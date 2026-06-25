#include "StatePattern_classic_generic/CoffeeMachine.hpp"
#include "StatePattern_classic_generic/States.hpp"
#include <iostream>

int main() {
    cg::CoffeeMachine m;
    std::cout << "=== Classic Generic State Pattern — Coffee Machine ===\n\n";

    std::cout << "--- Happy path: Cappuccino Medium ---\n";
    m.selectCoffee({coffee::CoffeeType::Cappuccino, coffee::CupSize::Medium});
    m.grindDone();
    m.brewDone();
    m.dispenseDone();

    std::cout << "\n--- Fault during dispensing ---\n";
    m.selectCoffee({coffee::CoffeeType::Latte, coffee::CupSize::Small});
    m.grindDone();
    m.brewDone();
    m.fault("Cup removed during dispensing");
    m.reset();

    std::cout << "\nFinal state: " << m.stateName() << "\n";
}
