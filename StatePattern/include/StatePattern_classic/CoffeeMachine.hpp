#pragma once
#include "ICoffeeMachineState.hpp"
#include "StatePattern_common/Domain.hpp"
#include <memory>
#include <optional>
#include <string>

class CoffeeMachine {
public:
    CoffeeMachine();
    ~CoffeeMachine() = default;

    // Public event interface
    void selectCoffee(coffee::CoffeeOrder order);
    void grindDone();
    void brewDone();
    void dispenseDone();
    void cancel();
    void fault(std::string_view reason);
    void reset();

    // Observers
    std::string_view stateName() const;
    bool hasOrder() const;
    const coffee::CoffeeOrder&   currentOrder()   const;
    const coffee::CoffeeProfile& currentProfile() const;
    const std::string&           faultReason()    const;

    // Called by concrete states to drive transitions and context mutations
    void transitionTo(std::unique_ptr<ICoffeeMachineState> next);
    void setupOrder(coffee::CoffeeOrder order);
    void clearOrder();
    void recordFault(std::string reason);

private:
    std::unique_ptr<ICoffeeMachineState> _state;
    std::optional<coffee::CoffeeOrder>   _order;
    std::optional<coffee::CoffeeProfile> _profile;
    std::string                          _faultReason;
};
