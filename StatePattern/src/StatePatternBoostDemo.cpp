#include "StatePattern_boost/CoffeeMachine.hpp"
#include <iostream>

int main() {
    bmsm::CoffeeMachine m;
    std::cout << "=== Boost.MSM State Pattern — Coffee Machine ===\n\n";

    std::cout << "--- Happy path: Espresso Medium ---\n";
    m.selectCoffee({coffee::CoffeeType::Espresso, coffee::CupSize::Medium});
    m.grindDone();
    m.brewDone();
    m.dispenseDone();

    std::cout << "\n--- Cancel during grinding ---\n";
    m.selectCoffee({coffee::CoffeeType::Latte, coffee::CupSize::Large});
    m.cancel();

    std::cout << "\n--- Fault during dispensing ---\n";
    m.selectCoffee({coffee::CoffeeType::Cappuccino, coffee::CupSize::Small});
    m.grindDone();
    m.brewDone();
    m.fault("Cup sensor offline");
    m.reset();

    std::cout << "\nFinal state: " << m.stateName() << "\n";
}
