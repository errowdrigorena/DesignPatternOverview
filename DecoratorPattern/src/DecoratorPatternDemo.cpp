#include <DecoratorPattern_classic/ConcreteComponent.hpp>
#include <DecoratorPattern_classic/ConcreteDecoratorA.hpp>
#include <DecoratorPattern_classic/ConcreteDecoratorB.hpp>
#include <DecoratorPattern_classic/ConcreteDecoratorC.hpp>

#include <iostream>
#include <memory>

int main()
{
    using namespace decorator_pattern_classic;

    auto with_a = std::make_unique<ConcreteDecoratorA>(std::make_unique<ConcreteComponent>());
    auto with_ab = std::make_unique<ConcreteDecoratorB>(std::make_unique<ConcreteDecoratorA>(std::make_unique<ConcreteComponent>()));
    auto with_abc = std::make_unique<ConcreteDecoratorC>(std::make_unique<ConcreteDecoratorB>(std::make_unique<ConcreteDecoratorA>(std::make_unique<ConcreteComponent>())));

    with_a->operation();
    std::cout << '\n';
    with_ab->operation();
    std::cout << '\n';
    with_abc->operation();
    std::cout << '\n';

    return 0;
}
