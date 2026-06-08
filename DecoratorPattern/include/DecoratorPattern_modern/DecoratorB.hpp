#pragma once

#include <iostream>

namespace decorator_pattern_modern {

template<typename Base>
struct DecoratorB : Base {
    void operation() const {
        Base::operation();
        std::cout << " + DecoratorB";
    }
};

}  // namespace decorator_pattern_modern
