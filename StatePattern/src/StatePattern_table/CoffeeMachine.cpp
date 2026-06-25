#include "StatePattern_table/CoffeeMachine.hpp"
#include <iostream>

namespace tbl {

using S    = CMState;
using E    = CMEvent;
using K    = CMEventKind;
using Next = TFiniteStateMachine<S, E, CoffeeMachineContext>::NextStateInfoWithContext;

// ── Transition table ──────────────────────────────────────────────────────────

std::unique_ptr<CoffeeMachine::FSM> CoffeeMachine::buildFSM()
{
    FSM::TransitionTable table{
        // ── Ready ─────────────────────────────────────────────────────────────
        { {S::Ready, E{K::SelectCoffee}}, [](CoffeeMachineContext ctx, E const& event) -> Next {
            if (!event.order.has_value()) {
                std::cout << "[Ready] FAULT: SelectCoffee requires an order\n";
                ctx.currentOrder.reset();
                ctx.profile.reset();
                ctx.faultReason = "SelectCoffee requires an order";
                return { S::Error, ctx, std::nullopt };
            }
            const auto& order = *event.order;
            std::cout << "[Ready] → Grinding  ("
                      << coffee::name(order.type) << ", "
                      << coffee::name(order.size) << ")\n";
            ctx.currentOrder = order;
            ctx.profile      = coffee::profileFor(order);
            return { S::Grinding, ctx, std::nullopt };
        }},
        { {S::Ready, E{K::Fault}}, [](CoffeeMachineContext ctx, E const& event) -> Next {
            std::cout << "[Ready] FAULT: " << event.faultReason << "\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            ctx.faultReason = event.faultReason;
            return { S::Error, ctx, std::nullopt };
        }},

        // ── Grinding ──────────────────────────────────────────────────────────
        { {S::Grinding, E{K::GrindDone}}, [](CoffeeMachineContext ctx, E const&) -> Next {
            std::cout << "[Grinding] → Brewing\n";
            return { S::Brewing, ctx, std::nullopt };
        }},
        { {S::Grinding, E{K::Cancel}}, [](CoffeeMachineContext ctx, E const&) -> Next {
            std::cout << "[Grinding] cancelled → Ready\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            return { S::Ready, ctx, std::nullopt };
        }},
        { {S::Grinding, E{K::Fault}}, [](CoffeeMachineContext ctx, E const& event) -> Next {
            std::cout << "[Grinding] FAULT: " << event.faultReason << "\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            ctx.faultReason = event.faultReason;
            return { S::Error, ctx, std::nullopt };
        }},

        // ── Brewing ───────────────────────────────────────────────────────────
        { {S::Brewing, E{K::BrewDone}}, [](CoffeeMachineContext ctx, E const&) -> Next {
            std::cout << "[Brewing] → Dispensing\n";
            return { S::Dispensing, ctx, std::nullopt };
        }},
        { {S::Brewing, E{K::Cancel}}, [](CoffeeMachineContext ctx, E const&) -> Next {
            std::cout << "[Brewing] cancelled → Ready\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            return { S::Ready, ctx, std::nullopt };
        }},
        { {S::Brewing, E{K::Fault}}, [](CoffeeMachineContext ctx, E const& event) -> Next {
            std::cout << "[Brewing] FAULT: " << event.faultReason << "\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            ctx.faultReason = event.faultReason;
            return { S::Error, ctx, std::nullopt };
        }},

        // ── Dispensing ────────────────────────────────────────────────────────
        { {S::Dispensing, E{K::DispenseDone}}, [](CoffeeMachineContext ctx, E const&) -> Next {
            std::cout << "[Dispensing] done → Ready\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            return { S::Ready, ctx, std::nullopt };
        }},
        { {S::Dispensing, E{K::Cancel}}, [](CoffeeMachineContext ctx, E const&) -> Next {
            std::cout << "[Dispensing] cancelled → Ready\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            return { S::Ready, ctx, std::nullopt };
        }},
        { {S::Dispensing, E{K::Fault}}, [](CoffeeMachineContext ctx, E const& event) -> Next {
            std::cout << "[Dispensing] FAULT: " << event.faultReason << "\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            ctx.faultReason = event.faultReason;
            return { S::Error, ctx, std::nullopt };
        }},

        // ── Error ─────────────────────────────────────────────────────────────
        { {S::Error, E{K::Reset}}, [](CoffeeMachineContext ctx, E const&) -> Next {
            std::cout << "[Error] reset → Ready\n";
            ctx.currentOrder.reset();
            ctx.profile.reset();
            ctx.faultReason.clear();
            return { S::Ready, ctx, std::nullopt };
        }},
    };

    return std::make_unique<FSM>(std::move(table), S::Ready);
}

// ── CoffeeMachine ─────────────────────────────────────────────────────────────

CoffeeMachine::CoffeeMachine()
    : _orchestrator(std::make_unique<Orchestrator>(buildFSM(), CoffeeMachineContext{}, kNormalPriority))
{}

// ── Immediate dispatch ────────────────────────────────────────────────────────

void CoffeeMachine::selectCoffee(coffee::CoffeeOrder order) {
    _orchestrator->QueueEvent(E{K::SelectCoffee, order}, kNormalPriority);
}

void CoffeeMachine::grindDone()    { _orchestrator->QueueEvent(E{K::GrindDone},    kNormalPriority); }
void CoffeeMachine::brewDone()     { _orchestrator->QueueEvent(E{K::BrewDone},     kNormalPriority); }
void CoffeeMachine::dispenseDone() { _orchestrator->QueueEvent(E{K::DispenseDone}, kNormalPriority); }
void CoffeeMachine::cancel()       { _orchestrator->QueueEvent(E{K::Cancel},       kCancelPriority); }
void CoffeeMachine::reset()        { _orchestrator->QueueEvent(E{K::Reset},        kResetPriority); }

void CoffeeMachine::fault(std::string_view reason) {
    _orchestrator->QueueEvent(E{K::Fault, std::nullopt, std::string(reason)}, kFaultPriority);
}

// ── Batch push ────────────────────────────────────────────────────────────────

void CoffeeMachine::pushSelectCoffee(coffee::CoffeeOrder order, int priority) {
    _orchestrator->PushEvent(E{K::SelectCoffee, order}, priority);
}
void CoffeeMachine::pushGrindDone   (int p) { _orchestrator->PushEvent(E{K::GrindDone},    p); }
void CoffeeMachine::pushBrewDone    (int p) { _orchestrator->PushEvent(E{K::BrewDone},     p); }
void CoffeeMachine::pushDispenseDone(int p) { _orchestrator->PushEvent(E{K::DispenseDone}, p); }
void CoffeeMachine::pushCancel      (int p) { _orchestrator->PushEvent(E{K::Cancel},       p); }
void CoffeeMachine::pushReset       (int p) { _orchestrator->PushEvent(E{K::Reset},        p); }

void CoffeeMachine::pushFault(std::string_view reason, int priority) {
    _orchestrator->PushEvent(E{K::Fault, std::nullopt, std::string(reason)}, priority);
}

void CoffeeMachine::processAll() { _orchestrator->ProcessQueued(); }

// ── Observers ─────────────────────────────────────────────────────────────────

CMState CoffeeMachine::currentState() const { return _orchestrator->GetCurrentState(); }

std::string_view CoffeeMachine::stateName() const {
    switch (currentState()) {
        case S::Ready:      return "Ready";
        case S::Grinding:   return "Grinding";
        case S::Brewing:    return "Brewing";
        case S::Dispensing: return "Dispensing";
        case S::Error:      return "Error";
        default:            return "Unknown";
    }
}

CoffeeMachineContext CoffeeMachine::context() const { return _orchestrator->getContext(); }

CoffeeMachine::Snapshot CoffeeMachine::snapshot() const {
    const auto snapshot = _orchestrator->getSnapshot();
    return {snapshot.state, snapshot.context};
}

} // namespace tbl
