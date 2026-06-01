#pragma once

#include <Shapes_strategy/DrawStrategy.hpp>

namespace shapes_strategy {

class ApiDrawStrategy final : public DrawStrategy {
public:
    void draw_circle(double radius) const override;
    void draw_rectangle(double width, double height) const override;
    void draw_triangle(double base, double height) const override;
};

}  // namespace shapes_strategy
