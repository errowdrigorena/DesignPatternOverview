#include "StatePattern_classic/States.hpp"
#include "StatePattern_classic/CoffeeMachine.hpp"
#include <iostream>

// ReadyState -------------------------------------------------------------------

void ReadyState::onSelectCoffee(CoffeeMachine& m, coffee::CoffeeOrder order) {
    std::cout << "[Ready] → Grinding  ("
              << coffee::name(order.type) << ", " << coffee::name(order.size) << ")\n";
    m.setupOrder(order);
    m.transitionTo(std::make_unique<GrindingState>());
}

void ReadyState::onFault(CoffeeMachine& m, std::string_view reason) {
    std::cout << "[Ready] FAULT: " << reason << "\n";
    m.recordFault(std::string(reason));
    m.transitionTo(std::make_unique<ErrorState>());
}

// GrindingState ----------------------------------------------------------------

void GrindingState::onGrindDone(CoffeeMachine& m) {
    std::cout << "[Grinding] → Brewing\n";
    m.transitionTo(std::make_unique<BrewingState>());
}

void GrindingState::onCancel(CoffeeMachine& m) {
    std::cout << "[Grinding] cancelled → Ready\n";
    m.clearOrder();
    m.transitionTo(std::make_unique<ReadyState>());
}

void GrindingState::onFault(CoffeeMachine& m, std::string_view reason) {
    std::cout << "[Grinding] FAULT: " << reason << "\n";
    m.recordFault(std::string(reason));
    m.transitionTo(std::make_unique<ErrorState>());
}

// BrewingState -----------------------------------------------------------------

void BrewingState::onBrewDone(CoffeeMachine& m) {
    std::cout << "[Brewing] → Dispensing\n";
    m.transitionTo(std::make_unique<DispensingState>());
}

void BrewingState::onFault(CoffeeMachine& m, std::string_view reason) {
    std::cout << "[Brewing] FAULT: " << reason << "\n";
    m.recordFault(std::string(reason));
    m.transitionTo(std::make_unique<ErrorState>());
}

// DispensingState --------------------------------------------------------------

void DispensingState::onDispenseDone(CoffeeMachine& m) {
    std::cout << "[Dispensing] done → Ready\n";
    m.clearOrder();
    m.transitionTo(std::make_unique<ReadyState>());
}

void DispensingState::onFault(CoffeeMachine& m, std::string_view reason) {
    std::cout << "[Dispensing] FAULT: " << reason << "\n";
    m.recordFault(std::string(reason));
    m.transitionTo(std::make_unique<ErrorState>());
}

// ErrorState -------------------------------------------------------------------

void ErrorState::onReset(CoffeeMachine& m) {
    std::cout << "[Error] reset → Ready\n";
    m.clearOrder();
    m.transitionTo(std::make_unique<ReadyState>());
}

void ErrorState::onFault(CoffeeMachine& m, std::string_view reason) {
    std::cout << "[Error] additional fault: " << reason << "\n";
    m.recordFault(std::string(reason));
}
