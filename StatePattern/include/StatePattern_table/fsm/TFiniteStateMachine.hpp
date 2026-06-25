#pragma once
#include <concepts>
#include <functional>
#include <unordered_map>
#include <utility>
#include <optional>
#include <mutex>
#include <type_traits>

class VoidByDefault {};

template<typename T>
concept FsmState = std::is_enum_v<T>;

// EventT must support std::hash (needed for the transition-table key) and ==
// (needed for unordered_map bucket lookup).
template<typename T>
concept FsmEvent = std::equality_comparable<T>
               && requires(T const& t) {
                      { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
                  };

// Finite state machine with a generic interface.
// Supports optional context, chained transitions, and efficient lookup.
// The transition table is indexed by (state, event) pairs.
//
// Thread-safety: handleEvent() must be serialized externally (TFSMOrchestrator does
// this when used with that wrapper). get_currentState() is safe to call concurrently,
// including from within a running action.
//
// WARNING: Actions must NOT call handleEvent() recursively — reentrancy is not
//          supported here. Use TFSMOrchestrator + extraEvent for chaining.
template<FsmState StateT, FsmEvent EventT, typename ContextT = VoidByDefault>
class TFiniteStateMachine
{

public:
    using TransitionKey = std::pair<StateT, EventT>;

    struct PairHash
    {
        std::size_t operator()(const TransitionKey& key) const
        {
            std::size_t h1 = std::hash<StateT>{}(key.first);
            std::size_t h2 = std::hash<EventT>{}(key.second);
            return h1 ^ (h2 << 1);
        }
    };

    struct NextStateInfoWithContext
    {
        StateT                 nextState;
        ContextT               context;
        std::optional<EventT>  extraEvent;
    };

    struct NextStateInfoWithoutContext
    {
        StateT                 nextState;
        std::optional<EventT>  extraEvent;
    };

    using Action = std::conditional_t<std::is_same_v<ContextT, VoidByDefault>,
                       std::function<NextStateInfoWithoutContext(EventT const&)>,
                       std::function<NextStateInfoWithContext(ContextT, EventT const&)>>;

    using TransitionTable = std::unordered_map<TransitionKey, Action, PairHash>;

    TFiniteStateMachine(TransitionTable table, StateT initial)
        : _transitions(std::move(table)), _currentState(initial) {}

    TFiniteStateMachine(TFiniteStateMachine&& other)
    {
        std::lock_guard lock(other._stateMutex);
        _transitions = std::move(other._transitions);
        _currentState = other._currentState;
    }

    TFiniteStateMachine& operator=(TFiniteStateMachine&& other)
    {
        if (this != &other)
        {
            std::scoped_lock lock(_stateMutex, other._stateMutex);
            _currentState = other._currentState;
            _transitions  = std::move(other._transitions);
        }
        return *this;
    }

    TFiniteStateMachine(const TFiniteStateMachine&)            = delete;
    TFiniteStateMachine& operator=(const TFiniteStateMachine&) = delete;

    template <typename T = ContextT, typename = std::enable_if_t<!std::is_same_v<T, VoidByDefault>>>
    std::pair<ContextT, std::optional<EventT>> handleEvent(EventT e, ContextT ctx)
    {
        Action action;
        {
            std::lock_guard stateLock(_stateMutex);
            auto it = _transitions.find({_currentState, e});
            if (it == _transitions.end())
                return {std::move(ctx), std::nullopt};
            action = it->second;
        }

        auto [nextState, nextCtx, extraEvent] = action(ctx, e);
        {
            std::lock_guard stateLock(_stateMutex);
            _currentState = nextState;
        }
        return {std::move(nextCtx), extraEvent};
    }

    template <typename T = ContextT, typename = std::enable_if_t<std::is_same_v<T, VoidByDefault>>>
    std::optional<EventT> handleEvent(EventT e)
    {
        Action action;
        {
            std::lock_guard stateLock(_stateMutex);
            auto it = _transitions.find({_currentState, e});
            if (it == _transitions.end())
                return std::nullopt;
            action = it->second;
        }

        auto [nextState, extraEvent] = action(e);
        {
            std::lock_guard stateLock(_stateMutex);
            _currentState = nextState;
        }
        return extraEvent;
    }

    StateT get_currentState() const
    {
        std::lock_guard lock(_stateMutex);
        return _currentState;
    }

private:
    mutable std::mutex _stateMutex;
    StateT             _currentState;
    TransitionTable    _transitions;
};
