#pragma once
#include <tuple>
#include <type_traits>

// ── Row ───────────────────────────────────────────────────────────────────────
// Describes one transition: source state, triggering event type, target state,
// and an action functor called as  ActionT{}(fsm, event).
template<auto SourceV, typename EventT, auto TargetV, typename ActionT>
struct Row {
    static constexpr auto source = SourceV;
    using Event                  = EventT;
    static constexpr auto target = TargetV;
    using Action                 = ActionT;
};

// ── StateMachineBase ──────────────────────────────────────────────────────────
// CRTP base templated on StateT (the enum) and Derived (the concrete machine
// definition, exactly as Boost.MSM does with state_machine_def<Derived>).
//
// Derived must provide:
//   using TransitionTable = std::tuple< Row<…>, Row<…>, … >;
//   static constexpr StateT initial_state = StateT::Xxx;
template<typename StateT, typename Derived>
class StateMachineBase {
public:
    template<typename EventT>
    void processEvent(EventT const& ev) {
        dispatchAll(static_cast<Derived&>(*this), _current, ev,
                    typename Derived::TransitionTable{});
    }

    StateT currentState() const { return _current; }

protected:
    explicit StateMachineBase(StateT initial) : _current(initial) {}

private:
    // Unpack the tuple type into a parameter pack and fold over it.
    template<typename EventT, typename... Rows>
    static void dispatchAll(Derived& fsm, StateT& current, EventT const& ev,
                            std::tuple<Rows...> /*tag*/) {
        (tryRow<Rows>(fsm, current, ev) || ...);  // short-circuits on first match
    }

    template<typename RowT, typename EventT>
    static bool tryRow(Derived& fsm, StateT& current, EventT const& ev) {
        if constexpr (std::is_same_v<typename RowT::Event, std::decay_t<EventT>>) {
            if (current == RowT::source) {
                typename RowT::Action{}(fsm, ev);
                current = RowT::target;
                return true;
            }
        }
        return false;
    }

    StateT _current;
};
