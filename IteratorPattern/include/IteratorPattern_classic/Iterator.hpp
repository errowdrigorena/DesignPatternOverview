#pragma once

#include <Shapes_traditional/Shapes.hpp>

namespace iterator_pattern_classic {

class Iterator {
public:
    virtual ~Iterator() = default;

    virtual void first() = 0;
    virtual void next() = 0;
    [[nodiscard]] virtual bool is_done() const = 0;
    [[nodiscard]] virtual const shapes_traditional::Shapes& current_item() const = 0;
};

}  // namespace iterator_pattern_classic
