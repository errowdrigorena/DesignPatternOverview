#pragma once
#include "StatePattern_common/Domain.hpp"
#include <cstddef>
#include <functional>
#include <optional>
#include <string>

namespace tbl {

enum class CMState { Ready, Grinding, Brewing, Dispensing, Error };

enum class CMEventKind { SelectCoffee, GrindDone, BrewDone, DispenseDone, Cancel, Fault, Reset };

// The queue owns events, so data needed to process one must travel with that
// event rather than being staged in shared context. Equality and hashing use
// only kind: the transition table is indexed by (state, event kind), while an
// action receives the complete event payload. SelectCoffee requires order;
// the transition validates that runtime invariant before using it.
struct CMEvent {
    CMEventKind kind;
    std::optional<coffee::CoffeeOrder> order;
    std::string faultReason;

    friend bool operator==(CMEvent const& lhs, CMEvent const& rhs) {
        return lhs.kind == rhs.kind;
    }
};

// Context carried atomically through every transition.
struct CoffeeMachineContext {
    std::optional<coffee::CoffeeOrder>   currentOrder;
    std::optional<coffee::CoffeeProfile> profile;
    std::string                          faultReason;
};

} // namespace tbl

template<>
struct std::hash<tbl::CMEvent> {
    std::size_t operator()(tbl::CMEvent const& event) const noexcept {
        return std::hash<tbl::CMEventKind>{}(event.kind);
    }
};
