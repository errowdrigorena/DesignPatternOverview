#pragma once

#include <iosfwd>

namespace composite_pattern_classic {

class Graphic {
public:
    virtual ~Graphic() = default;

    [[nodiscard]] virtual double area() const = 0;
    virtual void render(std::ostream& output, int depth = 0) const = 0;
};

}  // namespace composite_pattern_classic
