#pragma once

#include <PrototypePattern_classic/ShapePrototype.hpp>

namespace prototype_pattern_classic {

class RectanglePrototype final : public ShapePrototype {
public:
    RectanglePrototype(
        std::string name,
        std::string color,
        double x,
        double y,
        double width,
        double height);

    [[nodiscard]] RectanglePrototype* clone() const override;
    void set_name(std::string name) override;
    void set_color(std::string color) override;
    void move_to(double x, double y) override;
    void draw(std::ostream& output) const override;

private:
    std::string name_;
    std::string color_;
    double x_;
    double y_;
    double width_;
    double height_;
};

}  // namespace prototype_pattern_classic
