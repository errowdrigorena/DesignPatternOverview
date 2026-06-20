#pragma once

#include <iosfwd>
#include <memory>
#include <string>

namespace prototype_pattern_modern {

class ShapePrototype {
public:
    virtual ~ShapePrototype() = default;

    [[nodiscard]] virtual std::unique_ptr<ShapePrototype> clone() const = 0;
    virtual void set_name(std::string name) = 0;
    virtual void set_color(std::string color) = 0;
    virtual void move_to(double x, double y) = 0;
    virtual void draw(std::ostream& output) const = 0;
};

}  // namespace prototype_pattern_modern
