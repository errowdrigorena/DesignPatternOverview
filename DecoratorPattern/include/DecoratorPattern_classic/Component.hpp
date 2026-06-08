#pragma once

namespace decorator_pattern_classic {

class Component {
public:
    virtual ~Component() = default;
    virtual void operation() = 0;
};

}  // namespace decorator_pattern_classic
