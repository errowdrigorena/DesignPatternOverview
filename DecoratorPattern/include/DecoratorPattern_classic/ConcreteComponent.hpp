#pragma once

#include <DecoratorPattern_classic/Component.hpp>

namespace decorator_pattern_classic {

class ConcreteComponent final : public Component {
public:
    void operation() override;
};

}  // namespace decorator_pattern_classic
