#include <gtest/gtest.h>
#include "StatePattern_table/CoffeeMachine.hpp"
#include <stdexcept>
#include <memory>

using CT = coffee::CoffeeType;
using CS = coffee::CupSize;
using St = tbl::CMState;

namespace {

enum class RecoveryState { Ready, Done };
enum class RecoveryEvent { Throw, Continue };
enum class InspectState { Ready, Done };
enum class InspectEvent { Inspect };
enum class ContextState { Ready, Done };
enum class ContextEvent { Update };

using RecoveryFSM = TFiniteStateMachine<RecoveryState, RecoveryEvent, int>;
using RecoveryNext = RecoveryFSM::NextStateInfoWithContext;
using RecoveryOrchestrator = TFSMOrchestrator<RecoveryState, RecoveryEvent, int>;
using InspectFSM = TFiniteStateMachine<InspectState, InspectEvent, int>;
using InspectNext = InspectFSM::NextStateInfoWithContext;
using ContextFSM = TFiniteStateMachine<ContextState, ContextEvent, int>;
using ContextNext = ContextFSM::NextStateInfoWithContext;
using ContextOrchestrator = TFSMOrchestrator<ContextState, ContextEvent, int>;

} // namespace

// ── Immediate dispatch ────────────────────────────────────────────────────────

TEST(TableCoffeeMachine, StartsInReady) {
    tbl::CoffeeMachine m;
    const auto snapshot = m.snapshot();
    EXPECT_EQ(snapshot.state, St::Ready);
    EXPECT_FALSE(snapshot.context.currentOrder.has_value());
}

TEST(TableCoffeeMachine, HappyPath) {
    tbl::CoffeeMachine m;
    m.selectCoffee({CT::Latte, CS::Large});
    EXPECT_EQ(m.currentState(), St::Grinding);
    EXPECT_EQ(m.context().currentOrder->type, CT::Latte);
    EXPECT_TRUE(m.context().profile.has_value());

    m.grindDone();   EXPECT_EQ(m.currentState(), St::Brewing);
    m.brewDone();    EXPECT_EQ(m.currentState(), St::Dispensing);
    m.dispenseDone();
    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_FALSE(m.context().currentOrder.has_value());
}

TEST(TableCoffeeMachine, CancelDuringGrinding) {
    tbl::CoffeeMachine m;
    m.selectCoffee({CT::Espresso, CS::Small});
    m.cancel();
    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_FALSE(m.context().currentOrder.has_value());
}

TEST(TableCoffeeMachine, FaultAndReset) {
    tbl::CoffeeMachine m;
    m.selectCoffee({CT::Americano, CS::Medium});
    m.grindDone();
    m.fault("No water");
    EXPECT_EQ(m.currentState(), St::Error);
    EXPECT_EQ(m.context().faultReason, "No water");
    EXPECT_FALSE(m.context().currentOrder.has_value());
    EXPECT_FALSE(m.context().profile.has_value());

    m.reset();
    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_TRUE(m.context().faultReason.empty());
}

TEST(TEventQueue, SupportsMoveOnlyEvents) {
    TEventQueue<std::unique_ptr<int>> queue;
    queue.Push(std::make_unique<int>(42), 10);

    auto [event, priority] = queue.Pop();
    ASSERT_TRUE(event.has_value());
    EXPECT_EQ(**event, 42);
    EXPECT_EQ(priority, 10);
    EXPECT_TRUE(queue.Empty());
}

TEST(TFiniteStateMachine, ActionCanInspectCurrentState) {
    InspectFSM* fsmForAction = nullptr;
    InspectFSM::TransitionTable table{
        { {InspectState::Ready, InspectEvent::Inspect},
          [&fsmForAction](int context, InspectEvent const&) -> InspectNext {
              EXPECT_EQ(fsmForAction->get_currentState(), InspectState::Ready);
              return {InspectState::Done, context + 1, std::nullopt};
          } },
    };
    InspectFSM fsm(std::move(table), InspectState::Ready);
    fsmForAction = &fsm;

    auto [context, extraEvent] = fsm.handleEvent(InspectEvent::Inspect, 0);
    EXPECT_EQ(context, 1);
    EXPECT_FALSE(extraEvent.has_value());
    EXPECT_EQ(fsm.get_currentState(), InspectState::Done);
}

TEST(TFSMOrchestrator, PublishesStateAndContextAsOneCompletedSnapshot) {
    ContextFSM::TransitionTable table{
        { {ContextState::Ready, ContextEvent::Update},
          [](int, ContextEvent const&) -> ContextNext {
              return {ContextState::Done, 42, std::nullopt};
          } },
    };
    ContextOrchestrator orchestrator(
        std::make_unique<ContextFSM>(std::move(table), ContextState::Ready), 0, 10);

    orchestrator.QueueEvent(ContextEvent::Update, 10);
    const auto snapshot = orchestrator.getSnapshot();

    EXPECT_EQ(snapshot.state, ContextState::Done);
    EXPECT_EQ(snapshot.context, 42);
}

TEST(TFSMOrchestrator, RejectsSetContextCalledFromAnActionInsteadOfDeadlocking) {
    ContextOrchestrator* orchestratorForAction = nullptr;
    ContextFSM::TransitionTable table{
        { {ContextState::Ready, ContextEvent::Update},
          [&orchestratorForAction](int, ContextEvent const&) -> ContextNext {
              EXPECT_THROW(orchestratorForAction->setContext(99), std::logic_error);
              return {ContextState::Done, 1, std::nullopt};
          } },
    };
    ContextOrchestrator orchestrator(
        std::make_unique<ContextFSM>(std::move(table), ContextState::Ready), 0, 10);
    orchestratorForAction = &orchestrator;

    orchestrator.QueueEvent(ContextEvent::Update, 10);
    EXPECT_EQ(orchestrator.getContext(), 1);
}

TEST(TableCoffeeMachine, ProfileComputedOnSelection) {
    tbl::CoffeeMachine m;
    m.selectCoffee({CT::Espresso, CS::Medium});
    EXPECT_EQ(m.context().profile->grindLevel, 8);
    EXPECT_FLOAT_EQ(m.context().profile->waterMl, 60.f);
    EXPECT_FLOAT_EQ(m.context().profile->temperatureC, 94.f);
}

// ── Batch API + priority ordering ────────────────────────────────────────────

TEST(TableCoffeeMachineOrchestrator, FaultPreemptsSelectCoffeeWhenBatched) {
    // Push SelectCoffee(10) then Fault(0) without processing.
    // Fault must fire first: Ready+Fault → Error.
    // SelectCoffee then fires in Error state → no transition (ignored).
    tbl::CoffeeMachine m;
    m.pushSelectCoffee({CT::Cappuccino, CS::Large}, tbl::CoffeeMachine::kNormalPriority);
    m.pushFault("Boiler overheat", tbl::CoffeeMachine::kFaultPriority);
    m.processAll();

    EXPECT_EQ(m.currentState(), St::Error);
    EXPECT_EQ(m.context().faultReason, "Boiler overheat");
    EXPECT_FALSE(m.context().currentOrder.has_value());
}

TEST(TableCoffeeMachineOrchestrator, FaultKeepsItsOwnPayloadWhenBatched) {
    tbl::CoffeeMachine m;
    m.pushFault("First fault", 0);
    m.pushFault("Later fault", 1);
    m.processAll();

    EXPECT_EQ(m.currentState(), St::Error);
    EXPECT_EQ(m.context().faultReason, "First fault");
}

TEST(TableCoffeeMachineOrchestrator, CancelPreemptsGrindDoneWhenBatched) {
    // Already in Grinding. Push GrindDone(10) and Cancel(5) together.
    // Cancel must fire first → back to Ready before grinding finishes.
    tbl::CoffeeMachine m;
    m.selectCoffee({CT::Americano, CS::Small});    // immediate → Grinding
    EXPECT_EQ(m.currentState(), St::Grinding);

    m.pushGrindDone(tbl::CoffeeMachine::kNormalPriority);  // 10
    m.pushCancel   (tbl::CoffeeMachine::kCancelPriority);  // 5
    m.processAll();

    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_FALSE(m.context().currentOrder.has_value());
}

TEST(TableCoffeeMachineOrchestrator, BatchHappyPath) {
    // Push the entire normal cycle at once, then processAll().
    tbl::CoffeeMachine m;
    m.pushSelectCoffee({CT::Espresso, CS::Small}, tbl::CoffeeMachine::kNormalPriority);
    m.pushGrindDone();
    m.pushBrewDone();
    m.pushDispenseDone();
    m.processAll();

    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_FALSE(m.context().currentOrder.has_value());
}

TEST(TableCoffeeMachineOrchestrator, FaultPriorityIsLowestValue) {
    EXPECT_LT(tbl::CoffeeMachine::kFaultPriority,  tbl::CoffeeMachine::kCancelPriority);
    EXPECT_LT(tbl::CoffeeMachine::kCancelPriority, tbl::CoffeeMachine::kNormalPriority);
    EXPECT_LT(tbl::CoffeeMachine::kNormalPriority, tbl::CoffeeMachine::kResetPriority);
}

TEST(TFSMOrchestrator, ChainsExtraEventAfterTransition) {
    // An action can signal a follow-up event via extraEvent; the orchestrator must
    // queue and drain it before returning, without recursive handleEvent() calls.
    enum class ChainState { A, B, C };
    enum class ChainEvent { Trigger, Chained };

    using ChainFSM  = TFiniteStateMachine<ChainState, ChainEvent, int>;
    using ChainNext = ChainFSM::NextStateInfoWithContext;
    using ChainOrch = TFSMOrchestrator<ChainState, ChainEvent, int>;

    ChainFSM::TransitionTable table{
        { {ChainState::A, ChainEvent::Trigger},
          [](int ctx, ChainEvent) -> ChainNext {
              return {ChainState::B, ctx + 1, ChainEvent::Chained};
          }},
        { {ChainState::B, ChainEvent::Chained},
          [](int ctx, ChainEvent) -> ChainNext {
              return {ChainState::C, ctx + 1, std::nullopt};
          }},
    };

    ChainOrch orchestrator(
        std::make_unique<ChainFSM>(std::move(table), ChainState::A),
        0,   // initialContext
        10); // defaultExtraEventPriority

    orchestrator.QueueEvent(ChainEvent::Trigger, 10);

    EXPECT_EQ(orchestrator.GetCurrentState(), ChainState::C);
    EXPECT_EQ(orchestrator.getContext(), 2);
}

TEST(TableCoffeeMachine, SelectCoffeeWithoutOrderGoesToError) {
    // The Ready+SelectCoffee action validates that the event carries an order.
    // When missing, it transitions to Error rather than Grinding.
    // Exercised via the FSM directly since the public API always provides an order.
    using Orch = TFSMOrchestrator<tbl::CMState, tbl::CMEvent, tbl::CoffeeMachineContext>;

    Orch orch(tbl::CoffeeMachine::buildFSM(), tbl::CoffeeMachineContext{}, 10);
    orch.QueueEvent(tbl::CMEvent{tbl::CMEventKind::SelectCoffee}, 10);

    const auto snap = orch.getSnapshot();
    EXPECT_EQ(snap.state, tbl::CMState::Error);
    EXPECT_FALSE(snap.context.currentOrder.has_value());
    EXPECT_EQ(snap.context.faultReason, "SelectCoffee requires an order");
}

TEST(TFSMOrchestrator, RecoversAfterAnActionThrows) {
    RecoveryFSM::TransitionTable table{
        { {RecoveryState::Ready, RecoveryEvent::Throw},
          [](int, RecoveryEvent const&) -> RecoveryNext {
              throw std::runtime_error("expected test failure");
          } },
        { {RecoveryState::Ready, RecoveryEvent::Continue},
          [](int context, RecoveryEvent const&) -> RecoveryNext {
              return {RecoveryState::Done, context + 1, std::nullopt};
          } },
    };
    RecoveryOrchestrator orchestrator(
        std::make_unique<RecoveryFSM>(std::move(table), RecoveryState::Ready),
        int{},  // initialContext
        10);    // defaultExtraEventPriority (unused in this test)

    EXPECT_THROW(orchestrator.QueueEvent(RecoveryEvent::Throw, 0), std::runtime_error);
    orchestrator.QueueEvent(RecoveryEvent::Continue, 0);

    EXPECT_EQ(orchestrator.GetCurrentState(), RecoveryState::Done);
    EXPECT_EQ(orchestrator.getContext(), 1);
}

TEST(TFSMOrchestrator, ActionFailureDiscardsTheRestOfTheBatch) {
    RecoveryFSM::TransitionTable table{
        { {RecoveryState::Ready, RecoveryEvent::Throw},
          [](int, RecoveryEvent const&) -> RecoveryNext {
              throw std::runtime_error("expected batch failure");
          } },
        { {RecoveryState::Ready, RecoveryEvent::Continue},
          [](int context, RecoveryEvent const&) -> RecoveryNext {
              return {RecoveryState::Done, context + 1, std::nullopt};
          } },
    };
    RecoveryOrchestrator orchestrator(
        std::make_unique<RecoveryFSM>(std::move(table), RecoveryState::Ready),
        int{}, 10);

    orchestrator.PushEvent(RecoveryEvent::Throw, 0);
    orchestrator.PushEvent(RecoveryEvent::Continue, 0);

    EXPECT_THROW(orchestrator.ProcessQueued(), std::runtime_error);
    EXPECT_EQ(orchestrator.GetCurrentState(), RecoveryState::Ready);
    EXPECT_EQ(orchestrator.getContext(), 0);

    // The pending Continue was discarded with the failed batch.
    orchestrator.ProcessQueued();
    EXPECT_EQ(orchestrator.GetCurrentState(), RecoveryState::Ready);

    // A newly submitted event belongs to a fresh batch and still works.
    orchestrator.QueueEvent(RecoveryEvent::Continue, 0);
    EXPECT_EQ(orchestrator.GetCurrentState(), RecoveryState::Done);
    EXPECT_EQ(orchestrator.getContext(), 1);
}
