#pragma once
#include <string_view>
#include "StatePattern_common/Domain.hpp"

class CoffeeMachine;

class ICoffeeMachineState {
public:
    virtual ~ICoffeeMachineState() = default;

    virtual void onSelectCoffee(CoffeeMachine&, coffee::CoffeeOrder) {}
    virtual void onGrindDone   (CoffeeMachine&)                      {}
    virtual void onBrewDone    (CoffeeMachine&)                      {}
    virtual void onDispenseDone(CoffeeMachine&)                      {}
    virtual void onCancel      (CoffeeMachine&)                      {}
    virtual void onFault       (CoffeeMachine&, std::string_view)    {}
    virtual void onReset       (CoffeeMachine&)                      {}

    virtual std::string_view name() const = 0;
};
