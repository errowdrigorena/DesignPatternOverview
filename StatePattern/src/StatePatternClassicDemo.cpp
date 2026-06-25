#include "StatePattern_classic/CoffeeMachine.hpp"
#include <iostream>

int main() {
    CoffeeMachine m;
    std::cout << "=== Classic GoF State Pattern — Coffee Machine ===\n\n";

    std::cout << "--- Happy path: Espresso Small ---\n";
    m.selectCoffee({coffee::CoffeeType::Espresso, coffee::CupSize::Small});
    m.grindDone();
    m.brewDone();
    m.dispenseDone();

    std::cout << "\n--- Cancel during grinding: Latte Large ---\n";
    m.selectCoffee({coffee::CoffeeType::Latte, coffee::CupSize::Large});
    m.cancel();

    std::cout << "\n--- Fault during brewing: Americano Medium ---\n";
    m.selectCoffee({coffee::CoffeeType::Americano, coffee::CupSize::Medium});
    m.grindDone();
    m.fault("Water tank empty");
    m.reset();

    std::cout << "\nFinal state: " << m.stateName() << "\n";
}
