#include <DecoratorPattern_classic/ConcreteDecoratorC.hpp>

#include <iostream>

namespace decorator_pattern_classic {

void ConcreteDecoratorC::operation()
{
    Decorator::operation();
    std::cout << " + DecoratorC";
}

}  // namespace decorator_pattern_classic
