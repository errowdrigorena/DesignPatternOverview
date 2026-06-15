#pragma once

#include <DecoratorPattern_classic/Decorator.hpp>

namespace decorator_pattern_classic {

class ConcreteDecoratorA final : public Decorator {
public:
    using Decorator::Decorator;
    void operation() const override;
};

}  // namespace decorator_pattern_classic
