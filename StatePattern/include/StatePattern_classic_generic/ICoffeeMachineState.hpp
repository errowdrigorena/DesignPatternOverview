#pragma once
#include <string_view>
#include "StatePattern_common/Domain.hpp"

// Templating MachineT breaks the circular dependency: the interface does not
// need CoffeeMachine to be complete at definition time.
template<typename MachineT>
class ICoffeeMachineState {
public:
    virtual ~ICoffeeMachineState() = default;

    virtual void onSelectCoffee(MachineT&, coffee::CoffeeOrder) {}
    virtual void onGrindDone   (MachineT&)                      {}
    virtual void onBrewDone    (MachineT&)                      {}
    virtual void onDispenseDone(MachineT&)                      {}
    virtual void onCancel      (MachineT&)                      {}
    virtual void onFault       (MachineT&, std::string_view)    {}
    virtual void onReset       (MachineT&)                      {}

    virtual std::string_view name() const = 0;
};
