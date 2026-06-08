#pragma once

#include <iostream>

namespace decorator_pattern_modern {

// it is not possible to use it in a vector or a container, but it is possible to stack 
// decorators at compile time.
// it can be solved with type erasure, but it is not the point of this example.
template<typename Base>
struct DecoratorA : Base {
    void operation() const {
        Base::operation();
        std::cout << " + DecoratorA";
    }
};

}  // namespace decorator_pattern_modern
