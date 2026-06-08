#include <DecoratorPattern_modern/ConcreteComponent.hpp>
#include <DecoratorPattern_modern/DecoratorA.hpp>
#include <DecoratorPattern_modern/DecoratorB.hpp>
#include <DecoratorPattern_modern/DecoratorC.hpp>

#include <iostream>

int main()
{
    using namespace decorator_pattern_modern;

    DecoratorA<ConcreteComponent>                         with_a{};
    DecoratorB<DecoratorA<ConcreteComponent>>             with_ab{};
    DecoratorC<DecoratorB<DecoratorA<ConcreteComponent>>> with_abc{};

    with_a.operation();   std::cout << '\n';
    with_ab.operation();  std::cout << '\n';
    with_abc.operation(); std::cout << '\n';

    return 0;
}
