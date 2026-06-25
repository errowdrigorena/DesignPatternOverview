#pragma once
#include "StatePattern_common/Domain.hpp"
#include <variant>
#include <string>
#include <string_view>
#include <optional>
#include <iostream>

namespace sv {

// ── States (plain data structs — no inheritance) ──────────────────────────────

struct ReadyState {};

struct GrindingState {
    coffee::CoffeeOrder   order;
    coffee::CoffeeProfile profile;
};

struct BrewingState {
    coffee::CoffeeOrder   order;
    coffee::CoffeeProfile profile;
};

struct DispensingState {
    coffee::CoffeeOrder   order;
    coffee::CoffeeProfile profile;
};

struct ErrorState {
    std::string reason;
};

using State = std::variant<ReadyState, GrindingState, BrewingState, DispensingState, ErrorState>;

// ── Events (plain data structs) ───────────────────────────────────────────────

struct EvSelectCoffee { coffee::CoffeeOrder order; };
struct EvGrindDone    {};
struct EvBrewDone     {};
struct EvDispenseDone {};
struct EvCancel       {};
struct EvFault        { std::string reason; };
struct EvReset        {};

// ── Transition functions (ADL free functions) ─────────────────────────────────
// Default: ignore unknown (state, event) pairs — return the state unchanged.

template<typename StateT, typename EventT>
State onEvent(StateT const& s, EventT const&) { return s; }

inline State onEvent(ReadyState const&, EvSelectCoffee const& ev) {
    std::cout << "[Ready] → Grinding  ("
              << coffee::name(ev.order.type) << ", " << coffee::name(ev.order.size) << ")\n";
    return GrindingState{ev.order, coffee::profileFor(ev.order)};
}

inline State onEvent(GrindingState const& s, EvGrindDone const&) {
    std::cout << "[Grinding] → Brewing\n";
    return BrewingState{s.order, s.profile};
}

inline State onEvent(GrindingState const&, EvCancel const&) {
    std::cout << "[Grinding] cancelled → Ready\n";
    return ReadyState{};
}

inline State onEvent(BrewingState const& s, EvBrewDone const&) {
    std::cout << "[Brewing] → Dispensing\n";
    return DispensingState{s.order, s.profile};
}

inline State onEvent(DispensingState const&, EvDispenseDone const&) {
    std::cout << "[Dispensing] done → Ready\n";
    return ReadyState{};
}

// Fault transitions from any state (most-specialised wins for ErrorState+EvFault)
template<typename StateT>
State onEvent(StateT const&, EvFault const& ev) {
    std::cout << "[" << "?" << "] FAULT: " << ev.reason << "\n";
    return ErrorState{ev.reason};
}

// Keep the existing reason when already in Error — don't overwrite.
inline State onEvent(ErrorState const& s, EvFault const&) { return s; }

inline State onEvent(ErrorState const&, EvReset const&) {
    std::cout << "[Error] reset → Ready\n";
    return ReadyState{};
}

// ── Machine ───────────────────────────────────────────────────────────────────

class CoffeeMachine {
public:
    CoffeeMachine() : _state(ReadyState{}) {}

    template<typename EventT>
    void process(EventT const& ev) {
        _state = std::visit([&](auto const& s) { return onEvent(s, ev); }, _state);
    }

    std::string_view stateName() const {
        return std::visit([](auto const& s) -> std::string_view {
            using S = std::decay_t<decltype(s)>;
            if constexpr      (std::is_same_v<S, ReadyState>)      return "Ready";
            else if constexpr (std::is_same_v<S, GrindingState>)   return "Grinding";
            else if constexpr (std::is_same_v<S, BrewingState>)    return "Brewing";
            else if constexpr (std::is_same_v<S, DispensingState>) return "Dispensing";
            else                                                    return "Error";
        }, _state);
    }

    // Typed accessors for tests/demo
    bool hasOrder() const {
        return std::visit([](auto const& s) {
            using S = std::decay_t<decltype(s)>;
            return std::is_same_v<S, GrindingState>   ||
                   std::is_same_v<S, BrewingState>    ||
                   std::is_same_v<S, DispensingState>;
        }, _state);
    }

    std::optional<coffee::CoffeeOrder> currentOrder() const {
        return std::visit([](auto const& s) -> std::optional<coffee::CoffeeOrder> {
            using S = std::decay_t<decltype(s)>;
            if constexpr (std::is_same_v<S, GrindingState>   ||
                          std::is_same_v<S, BrewingState>    ||
                          std::is_same_v<S, DispensingState>)
                return s.order;
            return std::nullopt;
        }, _state);
    }

    const State& state() const { return _state; }

private:
    State _state;
};

} // namespace sv
