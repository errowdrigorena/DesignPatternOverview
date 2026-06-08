#pragma once

#include <iostream>

namespace decorator_pattern_modern {

struct ConcreteComponent {
    void operation() const {
        std::cout << "ConcreteComponent";
    }
};

}  // namespace decorator_pattern_modern
