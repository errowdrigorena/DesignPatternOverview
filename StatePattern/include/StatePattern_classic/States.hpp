#pragma once
#include "ICoffeeMachineState.hpp"

class ReadyState : public ICoffeeMachineState {
public:
    void onSelectCoffee(CoffeeMachine& m, coffee::CoffeeOrder order) override;
    void onFault       (CoffeeMachine& m, std::string_view reason)   override;
    std::string_view name() const override { return "Ready"; }
};

class GrindingState : public ICoffeeMachineState {
public:
    void onGrindDone(CoffeeMachine& m)                             override;
    void onCancel   (CoffeeMachine& m)                             override;
    void onFault    (CoffeeMachine& m, std::string_view reason)    override;
    std::string_view name() const override { return "Grinding"; }
};

class BrewingState : public ICoffeeMachineState {
public:
    void onBrewDone(CoffeeMachine& m)                             override;
    void onFault   (CoffeeMachine& m, std::string_view reason)    override;
    std::string_view name() const override { return "Brewing"; }
};

class DispensingState : public ICoffeeMachineState {
public:
    void onDispenseDone(CoffeeMachine& m)                             override;
    void onFault       (CoffeeMachine& m, std::string_view reason)    override;
    std::string_view name() const override { return "Dispensing"; }
};

class ErrorState : public ICoffeeMachineState {
public:
    void onReset(CoffeeMachine& m)                          override;
    void onFault(CoffeeMachine& m, std::string_view reason) override;
    std::string_view name() const override { return "Error"; }
};
