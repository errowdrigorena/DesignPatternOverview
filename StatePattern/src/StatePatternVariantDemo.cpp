#include "StatePattern_variant/CoffeeMachine.hpp"
#include <iostream>

int main() {
    sv::CoffeeMachine m;
    std::cout << "=== std::variant State Pattern — Coffee Machine ===\n\n";

    std::cout << "--- Happy path: Americano Large ---\n";
    m.process(sv::EvSelectCoffee{{coffee::CoffeeType::Americano, coffee::CupSize::Large}});
    m.process(sv::EvGrindDone{});
    m.process(sv::EvBrewDone{});
    m.process(sv::EvDispenseDone{});

    std::cout << "\n--- Ignored event (GrindDone when Ready) ---\n";
    m.process(sv::EvGrindDone{});
    std::cout << "State remains: " << m.stateName() << "\n";

    std::cout << "\n--- Fault during grinding: Espresso Small ---\n";
    m.process(sv::EvSelectCoffee{{coffee::CoffeeType::Espresso, coffee::CupSize::Small}});
    m.process(sv::EvFault{"Grinder jammed"});
    m.process(sv::EvReset{});

    std::cout << "\nFinal state: " << m.stateName() << "\n";
}
