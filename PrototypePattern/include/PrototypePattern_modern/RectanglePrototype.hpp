#pragma once

#include <PrototypePattern_modern/CloneableShape.hpp>

namespace prototype_pattern_modern {

class RectanglePrototype final : public CloneableShape<RectanglePrototype> {
public:
    RectanglePrototype(
        std::string name,
        std::string color,
        double x,
        double y,
        double width,
        double height);

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

}  // namespace prototype_pattern_modern
