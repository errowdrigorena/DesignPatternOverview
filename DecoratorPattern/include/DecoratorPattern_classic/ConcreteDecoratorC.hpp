#pragma once

#include <DecoratorPattern_classic/Decorator.hpp>

namespace decorator_pattern_classic {

class ConcreteDecoratorC final : public Decorator {
public:
    using Decorator::Decorator;
    void operation() const override;
};

}  // namespace decorator_pattern_classic
