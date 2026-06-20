#pragma once

#include <PrototypePattern_modern/CloneableShape.hpp>

namespace prototype_pattern_modern {

class CirclePrototype final : public CloneableShape<CirclePrototype> {
public:
    CirclePrototype(std::string name, std::string color, double x, double y, double radius);

    void set_name(std::string name) override;
    void set_color(std::string color) override;
    void move_to(double x, double y) override;
    void draw(std::ostream& output) const override;

private:
    std::string name_;
    std::string color_;
    double x_;
    double y_;
    double radius_;
};

}  // namespace prototype_pattern_modern
