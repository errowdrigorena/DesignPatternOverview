#include <DecoratorPattern_classic/ConcreteDecoratorB.hpp>

#include <iostream>

namespace decorator_pattern_classic {

void ConcreteDecoratorB::operation()
{
    Decorator::operation();
    std::cout << " + DecoratorB";
}

}  // namespace decorator_pattern_classic
