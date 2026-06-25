#include "StatePattern_boost_inspired/CoffeeMachine.hpp"
#include <iostream>

int main() {
    bi::CoffeeMachineDef m;
    std::cout << "=== Boost-Inspired Compile-Time Table — Coffee Machine ===\n\n";

    std::cout << "--- Happy path: Cappuccino Large ---\n";
    m.selectCoffee({coffee::CoffeeType::Cappuccino, coffee::CupSize::Large});
    m.grindDone();
    m.brewDone();
    m.dispenseDone();

    std::cout << "\n--- Cancel during grinding ---\n";
    m.selectCoffee({coffee::CoffeeType::Americano, coffee::CupSize::Small});
    m.cancel();

    std::cout << "\n--- Fault during brewing ---\n";
    m.selectCoffee({coffee::CoffeeType::Espresso, coffee::CupSize::Medium});
    m.grindDone();
    m.fault("Boiler overheat");
    m.reset();

    std::cout << "\nFinal state: " << m.stateName() << "\n";
}
