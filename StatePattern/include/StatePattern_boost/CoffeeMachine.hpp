#pragma once
#include "StatePattern_common/Domain.hpp"

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/mpl/vector.hpp>

#include <optional>
#include <string>
#include <string_view>
#include <iostream>

namespace bmsm {

namespace msm   = boost::msm;
namespace mpl   = boost::mpl;
namespace front = boost::msm::front;

// ── Events ────────────────────────────────────────────────────────────────────

struct EvSelectCoffee { coffee::CoffeeOrder order; };
struct EvGrindDone    {};
struct EvBrewDone     {};
struct EvDispenseDone {};
struct EvCancel       {};
struct EvFault        { std::string reason; };
struct EvReset        {};

// ── Flags (used to query active state) ───────────────────────────────────────

struct FlagReady      {};
struct FlagGrinding   {};
struct FlagBrewing    {};
struct FlagDispensing {};
struct FlagError      {};

// ── Front-end definition ──────────────────────────────────────────────────────

struct CoffeeFSMDef : public msm::front::state_machine_def<CoffeeFSMDef> {

    // Context data lives in the def — same as our Boost-inspired version.
    std::optional<coffee::CoffeeOrder>   order;
    std::optional<coffee::CoffeeProfile> profile;
    std::string                          faultReason;

    // ── States ────────────────────────────────────────────────────────────────

    struct Ready_ : public msm::front::state<> {
        using flag_list = mpl::vector<FlagReady>;
        template<typename Evt, typename FSM>
        void on_entry(Evt const&, FSM&) { std::cout << "[MSM] → Ready\n"; }
    };

    struct Grinding_ : public msm::front::state<> {
        using flag_list = mpl::vector<FlagGrinding>;
        template<typename Evt, typename FSM>
        void on_entry(Evt const&, FSM&) { std::cout << "[MSM] → Grinding\n"; }
    };

    struct Brewing_ : public msm::front::state<> {
        using flag_list = mpl::vector<FlagBrewing>;
        template<typename Evt, typename FSM>
        void on_entry(Evt const&, FSM&) { std::cout << "[MSM] → Brewing\n"; }
    };

    struct Dispensing_ : public msm::front::state<> {
        using flag_list = mpl::vector<FlagDispensing>;
        template<typename Evt, typename FSM>
        void on_entry(Evt const&, FSM&) { std::cout << "[MSM] → Dispensing\n"; }
    };

    struct Error_ : public msm::front::state<> {
        using flag_list = mpl::vector<FlagError>;
        template<typename Evt, typename FSM>
        void on_entry(Evt const&, FSM&) { std::cout << "[MSM] → Error\n"; }
    };

    using initial_state = Ready_;

    // ── Actions ───────────────────────────────────────────────────────────────

    struct SetupOrder {
        template<typename Evt, typename FSM, typename Src, typename Tgt>
        void operator()(Evt const& ev, FSM& fsm, Src&, Tgt&) {
            std::cout << "[MSM] Selecting "
                      << coffee::name(ev.order.type) << " ("
                      << coffee::name(ev.order.size) << ")\n";
            fsm.order   = ev.order;
            fsm.profile = coffee::profileFor(ev.order);
        }
    };

    struct ClearOrder {
        template<typename Evt, typename FSM, typename Src, typename Tgt>
        void operator()(Evt const&, FSM& fsm, Src&, Tgt&) {
            fsm.order.reset();
            fsm.profile.reset();
            fsm.faultReason.clear();
        }
    };

    struct RecordFault {
        template<typename Evt, typename FSM, typename Src, typename Tgt>
        void operator()(Evt const& ev, FSM& fsm, Src&, Tgt&) {
            std::cout << "[MSM] FAULT: " << ev.reason << "\n";
            fsm.faultReason = ev.reason;
        }
    };

    // ── Transition table ──────────────────────────────────────────────────────

    using none = msm::front::none;

    struct transition_table : mpl::vector<
        //  Source       Event           Target        Action       Guard
        front::Row< Ready_,      EvSelectCoffee, Grinding_,   SetupOrder,   none >,
        front::Row< Grinding_,   EvGrindDone,    Brewing_,    none,         none >,
        front::Row< Grinding_,   EvCancel,       Ready_,      ClearOrder,   none >,
        front::Row< Brewing_,    EvBrewDone,     Dispensing_, none,         none >,
        front::Row< Dispensing_, EvDispenseDone, Ready_,      ClearOrder,   none >,
        front::Row< Ready_,      EvFault,        Error_,      RecordFault,  none >,
        front::Row< Grinding_,   EvFault,        Error_,      RecordFault,  none >,
        front::Row< Brewing_,    EvFault,        Error_,      RecordFault,  none >,
        front::Row< Dispensing_, EvFault,        Error_,      RecordFault,  none >,
        front::Row< Error_,      EvReset,        Ready_,      ClearOrder,   none >
    > {};

    // Suppress MSM's default std::cerr warning on unhandled events.
    template<typename FSM, typename Evt>
    void no_transition(Evt const&, FSM&, int /*state*/) {}
};

// ── Back-end wrapper (the usable machine) ─────────────────────────────────────

class CoffeeMachine {
    using Backend = msm::back::state_machine<CoffeeFSMDef>;

public:
    CoffeeMachine() { _fsm.start(); }

    void selectCoffee(coffee::CoffeeOrder o)  { _fsm.process_event(EvSelectCoffee{o}); }
    void grindDone()                          { _fsm.process_event(EvGrindDone{}); }
    void brewDone()                           { _fsm.process_event(EvBrewDone{}); }
    void dispenseDone()                       { _fsm.process_event(EvDispenseDone{}); }
    void cancel()                             { _fsm.process_event(EvCancel{}); }
    void fault(std::string_view r)            { _fsm.process_event(EvFault{std::string(r)}); }
    void reset()                              { _fsm.process_event(EvReset{}); }

    std::string_view stateName() const {
        if (_fsm.is_flag_active<FlagReady>())      return "Ready";
        if (_fsm.is_flag_active<FlagGrinding>())   return "Grinding";
        if (_fsm.is_flag_active<FlagBrewing>())    return "Brewing";
        if (_fsm.is_flag_active<FlagDispensing>()) return "Dispensing";
        if (_fsm.is_flag_active<FlagError>())      return "Error";
        return "Unknown";
    }

    bool hasOrder()         const { return _fsm.order.has_value(); }
    const std::string& faultReason() const { return _fsm.faultReason; }
    const std::optional<coffee::CoffeeOrder>&   order()   const { return _fsm.order; }
    const std::optional<coffee::CoffeeProfile>& profile() const { return _fsm.profile; }

private:
    Backend _fsm;
};

} // namespace bmsm
