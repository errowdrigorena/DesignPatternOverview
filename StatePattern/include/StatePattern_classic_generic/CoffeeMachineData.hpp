#pragma once
#include "StatePattern_common/Domain.hpp"
#include <optional>
#include <string>

namespace cg {

struct CoffeeMachineData {
    std::optional<coffee::CoffeeOrder>   order;
    std::optional<coffee::CoffeeProfile> profile;
    std::string                          faultReason;
};

} // namespace cg
