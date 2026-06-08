#pragma once

#include <DecoratorPattern_classic/Decorator.hpp>

namespace decorator_pattern_classic {

class ConcreteDecoratorB final : public Decorator {
public:
    using Decorator::Decorator;
    void operation() override;
};

}  // namespace decorator_pattern_classic
