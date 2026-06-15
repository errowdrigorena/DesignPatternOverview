#pragma once

#include <DecoratorPattern_classic/Component.hpp>

#include <memory>

namespace decorator_pattern_classic {

class Decorator : public Component {
public:
    explicit Decorator(std::unique_ptr<Component> component);
    void operation() const override;

protected:
    std::unique_ptr<Component> component_;
};

}  // namespace decorator_pattern_classic
