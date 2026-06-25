#pragma once
#include "StateMachineBase.hpp"
#include "StatePattern_common/Domain.hpp"
#include <optional>
#include <string>
#include <string_view>
#include <iostream>

namespace bi {

// ── States ────────────────────────────────────────────────────────────────────

enum class CMState { Ready, Grinding, Brewing, Dispensing, Error };

// ── Events ────────────────────────────────────────────────────────────────────

struct EvSelectCoffee { coffee::CoffeeOrder order; };
struct EvGrindDone    {};
struct EvBrewDone     {};
struct EvDispenseDone {};
struct EvCancel       {};
struct EvFault        { std::string reason; };
struct EvReset        {};

// ── Actions ───────────────────────────────────────────────────────────────────
// Each action is a callable struct — same convention Boost.MSM uses.

struct NoAction {
    void operator()(auto& /*fsm*/, auto const& /*ev*/) const {}
};

struct DoSetupOrder {
    void operator()(auto& fsm, EvSelectCoffee const& ev) const {
        std::cout << "[Ready] → Grinding  ("
                  << coffee::name(ev.order.type) << ", "
                  << coffee::name(ev.order.size) << ")\n";
        fsm.order   = ev.order;
        fsm.profile = coffee::profileFor(ev.order);
    }
};

struct DoClearOrder {
    void operator()(auto& fsm, auto const&) const {
        fsm.order.reset();
        fsm.profile.reset();
        fsm.faultReason.clear();
    }
};

struct DoRecordFault {
    void operator()(auto& fsm, EvFault const& ev) const {
        std::cout << "[?] FAULT: " << ev.reason << "\n";
        fsm.faultReason = ev.reason;
    }
};

struct DoLogGrindDone {
    void operator()(auto& /*fsm*/, EvGrindDone const&) const {
        std::cout << "[Grinding] → Brewing\n";
    }
};

struct DoLogBrewDone {
    void operator()(auto& /*fsm*/, EvBrewDone const&) const {
        std::cout << "[Brewing] → Dispensing\n";
    }
};

struct DoLogDispenseDone {
    void operator()(auto& fsm, EvDispenseDone const& ev) const {
        std::cout << "[Dispensing] done → Ready\n";
        DoClearOrder{}(fsm, ev);
    }
};

struct DoLogCancel {
    void operator()(auto& fsm, EvCancel const& ev) const {
        std::cout << "[Grinding] cancelled → Ready\n";
        DoClearOrder{}(fsm, ev);
    }
};

struct DoReset {
    void operator()(auto& fsm, EvReset const& ev) const {
        std::cout << "[Error] reset → Ready\n";
        DoClearOrder{}(fsm, ev);
    }
};

// ── Machine definition (context + transition table) ───────────────────────────

using S = CMState;

struct CoffeeMachineDef : public StateMachineBase<CMState, CoffeeMachineDef> {
    CoffeeMachineDef() : StateMachineBase(CMState::Ready) {}

    // Context lives directly in the definition — just like Boost.MSM.
    std::optional<coffee::CoffeeOrder>   order;
    std::optional<coffee::CoffeeProfile> profile;
    std::string                          faultReason;

    // Transition table: std::tuple of Row<source, Event, target, Action>.
    // The base class iterates it at compile time; at runtime it is a linear
    // scan that short-circuits on the first matching row.
    using TransitionTable = std::tuple<
        Row<S::Ready,      EvSelectCoffee, S::Grinding,   DoSetupOrder   >,
        Row<S::Grinding,   EvGrindDone,    S::Brewing,    DoLogGrindDone >,
        Row<S::Grinding,   EvCancel,       S::Ready,      DoLogCancel    >,
        Row<S::Brewing,    EvBrewDone,     S::Dispensing, DoLogBrewDone  >,
        Row<S::Dispensing, EvDispenseDone, S::Ready,      DoLogDispenseDone>,
        Row<S::Ready,      EvFault,        S::Error,      DoRecordFault  >,
        Row<S::Grinding,   EvFault,        S::Error,      DoRecordFault  >,
        Row<S::Brewing,    EvFault,        S::Error,      DoRecordFault  >,
        Row<S::Dispensing, EvFault,        S::Error,      DoRecordFault  >,
        Row<S::Error,      EvReset,        S::Ready,      DoReset        >
    >;

    // Public interface — thin wrappers that forward to processEvent()
    void selectCoffee(coffee::CoffeeOrder o) { processEvent(EvSelectCoffee{o}); }
    void grindDone()                         { processEvent(EvGrindDone{}); }
    void brewDone()                          { processEvent(EvBrewDone{}); }
    void dispenseDone()                      { processEvent(EvDispenseDone{}); }
    void cancel()                            { processEvent(EvCancel{}); }
    void fault(std::string_view r)           { processEvent(EvFault{std::string(r)}); }
    void reset()                             { processEvent(EvReset{}); }

    std::string_view stateName() const {
        switch (currentState()) {
            case S::Ready:      return "Ready";
            case S::Grinding:   return "Grinding";
            case S::Brewing:    return "Brewing";
            case S::Dispensing: return "Dispensing";
            case S::Error:      return "Error";
        }
        return "Unknown";
    }
};

} // namespace bi
