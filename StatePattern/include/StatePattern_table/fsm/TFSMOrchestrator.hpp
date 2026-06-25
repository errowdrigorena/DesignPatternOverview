#pragma once
#include "TPrioritizedEventQueue.hpp"
#include "TFiniteStateMachine.hpp"
#include <concepts>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <tuple>
#include <utility>

// Wraps TFiniteStateMachine with a prioritized event queue to enable safe
// reentrancy: if an action triggers another event (via extraEvent), the new
// event is placed in the queue rather than processed recursively, preventing
// deadlock and maintaining a clean LIFO-free execution model.
//
// Priority convention (lower value = processed first):
//   0  — emergency / fault
//   5  — cancel / interrupt
//   10 — normal process steps
//   15 — housekeeping / reset
//
// Thread-safety contract:
//   - TEventQueue manages its own internal mutex; Push/Pop need no external lock.
//   - Published state and context are updated together under _mutex. Individual
//     getters therefore return values from a completed transition, never a
//     half-applied transition. Use getSnapshot() when both values must belong
//     to the same observation.
//   - setContext() cannot be called by an action running in this orchestrator:
//     it would otherwise wait for the action that is waiting on it. Such a call
//     throws std::logic_error instead of deadlocking.
//   - QueueEvent() is synchronous only when it acquires the consumer role. If
//     another thread is already draining, it reliably enqueues the event but
//     returns without waiting for that thread to process it. This keeps action
//     initiated QueueEvent() calls safe and non-recursive.
//   - If an action throws, the current event has failed and every event still
//     pending in that drain is discarded. The exception is then propagated.
//     A later QueueEvent()/ProcessQueued() starts a fresh batch.
//   - Orchestrators are intentionally non-movable: moving an object while a
//     caller may still dispatch to it has no meaningful safe ownership model.
// ContextT must be semiregular: default-constructible (re-declared each retry
// in TryProcessQueued) + copyable (snapshotted from/into _context each batch).
// PriorityT must be totally ordered (used in TPrioritizedEvent::operator<).
template<FsmState StateT, FsmEvent EventT,
         std::semiregular ContextT,
         std::totally_ordered PriorityT = int>
class TFSMOrchestrator
{

public:
    using FSM         = TFiniteStateMachine<StateT, EventT, ContextT>;
    using EventQueueT = TEventQueue<EventT, PriorityT>;

    struct Snapshot
    {
        StateT   state;
        ContextT context;
    };

    // defaultExtraEventPriority: priority given to events chained via extraEvent.
    // Pass the application's "normal" priority so a Fault transition does not
    // accidentally give its chained cleanup event emergency priority (0).
    // defaultExtraEventPriority has no safe universal default (PriorityT{} = 0
    // for int, which is emergency priority); callers must pass explicitly.
    explicit TFSMOrchestrator(std::unique_ptr<FSM> fsm,
                               ContextT  initialContext,
                               PriorityT defaultExtraEventPriority)
        : _fsm(std::move(fsm))
        , _isEventInProgress(false)
        , _context(std::move(initialContext))
        , _defaultExtraEventPriority(std::move(defaultExtraEventPriority))
    {
        if (!_fsm)
            throw std::invalid_argument("TFSMOrchestrator requires a non-null FSM");
        _publishedState = _fsm->get_currentState();
    }

    ~TFSMOrchestrator() = default;

    TFSMOrchestrator(const TFSMOrchestrator&)            = delete;
    TFSMOrchestrator& operator=(const TFSMOrchestrator&) = delete;

    TFSMOrchestrator(TFSMOrchestrator&&)            = delete;
    TFSMOrchestrator& operator=(TFSMOrchestrator&&) = delete;

    // ── Normal event dispatch: queue + process immediately ───────────────────
    // TEventQueue is thread-safe; no extra lock needed around Push.
    void QueueEvent(EventT ev, PriorityT priority)
    {
        _eventQueue.Push(std::move(ev), std::move(priority));
        TryProcessQueued();
    }

    // ── Batch API: push without processing, call ProcessQueued() later ───────
    void PushEvent(EventT ev, PriorityT priority)
    {
        _eventQueue.Push(std::move(ev), std::move(priority));
    }

    void ProcessQueued()
    {
        TryProcessQueued();
    }

    // ── Context accessors ─────────────────────────────────────────────────────
    ContextT getContext() const
    {
        std::lock_guard lock(_mutex);
        return _context;
    }

    void setContext(ContextT ctx)
    {
        std::unique_lock lock(_mutex);
        if (_isEventInProgress && _processingThread == std::this_thread::get_id())
            throw std::logic_error("setContext() cannot be called from an FSM action");
        _processingFinished.wait(lock, [this] { return !_isEventInProgress; });
        _context = std::move(ctx);
    }

    // ── State inspection ──────────────────────────────────────────────────────
    StateT GetCurrentState() const
    {
        std::lock_guard lock(_mutex);
        return _publishedState;
    }

    Snapshot getSnapshot() const
    {
        std::lock_guard lock(_mutex);
        return {_publishedState, _context};
    }

private:
    void TryProcessQueued()
    {
        // Snapshot _context and claim exclusive processing — both under _mutex.
        // setContext() waits for the current drain to finish, so it cannot be
        // overwritten by this final context write-back.
        for (;;)
        {
            ContextT localCtx;
            {
                std::lock_guard lock(_mutex);
                if (_isEventInProgress)
                    return;
                localCtx = _context;
                _isEventInProgress = true;
                _processingThread = std::this_thread::get_id();
            }

            try {
                auto [ev, pri] = _eventQueue.Pop();
                while (ev.has_value())
                {
                    auto [updatedCtx, extraEvent] = _fsm->handleEvent(ev.value(), localCtx);
                    localCtx = std::move(updatedCtx);
                    publishTransition(localCtx);

                    // Use _defaultExtraEventPriority, not the parent's priority, so a
                    // Fault(0) transition doesn't give its chained cleanup event
                    // emergency priority by accident.
                    if (extraEvent.has_value())
                        _eventQueue.Push(extraEvent.value(), _defaultExtraEventPriority);

                    std::tie(ev, pri) = _eventQueue.Pop();
                }
            } catch (...) {
                // An action failure aborts this batch. The current event was
                // already popped; discard the remaining queued events so they
                // cannot run later against a partially failed workflow.
                _eventQueue.Clear();
                finishProcessing(std::move(localCtx));
                throw;
            }

            finishProcessing(std::move(localCtx));

            // An event can arrive after the final Pop() and before the flag is
            // released. Iterate to claim and drain it without growing the stack.
            if (_eventQueue.Empty())
                return;
        }
    }

    void finishProcessing(ContextT context)
    {
        {
            std::lock_guard lock(_mutex);
            _context = std::move(context);
            _publishedState = _fsm->get_currentState();
            _isEventInProgress = false;
            _processingThread = {};
        }
        _processingFinished.notify_all();
    }

    void publishTransition(ContextT const& context)
    {
        std::lock_guard lock(_mutex);
        _context = context;
        _publishedState = _fsm->get_currentState();
    }

    std::unique_ptr<FSM>  _fsm;
    EventQueueT           _eventQueue;        // thread-safe internally
    bool                  _isEventInProgress;
    ContextT              _context;           // protected by _mutex
    StateT                _publishedState{};  // protected by _mutex
    std::thread::id       _processingThread;  // protected by _mutex
    PriorityT             _defaultExtraEventPriority;
    mutable std::mutex    _mutex;
    std::condition_variable _processingFinished;
};
