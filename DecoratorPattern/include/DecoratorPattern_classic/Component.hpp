#pragma once

namespace decorator_pattern_classic {

class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;
};

}  // namespace decorator_pattern_classic
