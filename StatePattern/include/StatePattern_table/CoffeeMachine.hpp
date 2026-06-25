#pragma once
#include "CoffeeMachineContext.hpp"
#include "fsm/TFSMOrchestrator.hpp"
#include <memory>
#include <string_view>

namespace tbl {

// Coffee machine built on top of TFiniteStateMachine + TFSMOrchestrator.
//
// Two dispatch modes are offered to showcase the orchestrator:
//
//  ┌─ Immediate mode ──────────────────────────────────────────────────────────┐
//  │  selectCoffee() / grindDone() / fault() / …                              │
//  │  Queue the event and trigger processing right away. If another thread is │
//  │  already draining, the call returns after enqueueing.                    │
//  └───────────────────────────────────────────────────────────────────────────┘
//  ┌─ Batch mode ───────────────────────────────────────────────────────────────┐
//  │  pushSelectCoffee() / pushFault() / pushGrindDone() / …                  │
//  │  Accumulate events in the priority queue without processing.              │
//  │  Call processAll() once to drain the queue in priority order.            │
//  │                                                                           │
//  │  Priority convention (lower = processed first):                          │
//  │    kFaultPriority  = 0   ── emergency stop                               │
//  │    kCancelPriority = 5   ── interrupt current operation                  │
//  │    kNormalPriority = 10  ── regular process steps                        │
//  │    kResetPriority  = 15  ── housekeeping (only after everything else)     │
//  └───────────────────────────────────────────────────────────────────────────┘
class CoffeeMachine {
    using FSM          = TFiniteStateMachine<CMState, CMEvent, CoffeeMachineContext>;
    using Orchestrator = TFSMOrchestrator<CMState, CMEvent, CoffeeMachineContext>;

public:
    struct Snapshot {
        CMState              state;
        CoffeeMachineContext context;
    };

    static constexpr int kFaultPriority  = 0;
    static constexpr int kCancelPriority = 5;
    static constexpr int kNormalPriority = 10;
    static constexpr int kResetPriority  = 15;

    static std::unique_ptr<FSM> buildFSM();

    CoffeeMachine();

    // ── Immediate dispatch ────────────────────────────────────────────────────
    void selectCoffee(coffee::CoffeeOrder order);
    void grindDone();
    void brewDone();
    void dispenseDone();
    void cancel();
    void fault(std::string_view reason);
    void reset();

    // ── Batch push (no processing until processAll()) ─────────────────────────
    void pushSelectCoffee(coffee::CoffeeOrder order, int priority = kNormalPriority);
    void pushGrindDone   (int priority = kNormalPriority);
    void pushBrewDone    (int priority = kNormalPriority);
    void pushDispenseDone(int priority = kNormalPriority);
    void pushCancel      (int priority = kCancelPriority);
    void pushFault       (std::string_view reason, int priority = kFaultPriority);
    void pushReset       (int priority = kResetPriority);
    void processAll();

    // ── Observers ─────────────────────────────────────────────────────────────
    CMState              currentState() const;
    std::string_view     stateName()    const;
    CoffeeMachineContext context()      const;   // returns a snapshot copy
    Snapshot             snapshot()     const;   // state and context from one instant

private:
    std::unique_ptr<Orchestrator> _orchestrator;
};

} // namespace tbl
