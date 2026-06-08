#include <DecoratorPattern_classic/ConcreteDecoratorA.hpp>

#include <iostream>

namespace decorator_pattern_classic {

void ConcreteDecoratorA::operation()
{
    Decorator::operation();
    std::cout << " + DecoratorA";
}

}  // namespace decorator_pattern_classic
