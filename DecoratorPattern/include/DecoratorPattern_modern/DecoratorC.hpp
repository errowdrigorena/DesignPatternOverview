#pragma once

#include <iostream>

namespace decorator_pattern_modern {
    
// it is not possible to use it in a vector or a container, but it is possible to stack 
// decorators at compile time.
// it can be solved with type erasure, but it is not the point of this example.
template<typename Base>
struct DecoratorC : Base {
    void operation() const {
        Base::operation();
        std::cout << " + DecoratorC";
    }
};

}  // namespace decorator_pattern_modern
