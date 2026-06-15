#include <DecoratorPattern_classic/ConcreteComponent.hpp>

#include <iostream>

namespace decorator_pattern_classic {

void ConcreteComponent::operation() const
{
    std::cout << "ConcreteComponent";
}

}  // namespace decorator_pattern_classic
