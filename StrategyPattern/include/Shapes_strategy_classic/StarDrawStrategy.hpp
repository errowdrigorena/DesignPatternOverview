#pragma once

#include <Shapes_strategy_classic/DrawStrategy.hpp>

namespace shapes_strategy {

class StarDrawStrategy final : public DrawStrategy {
public:
    void draw_circle(double radius) const override;
    void draw_rectangle(double width, double height) const override;
    void draw_triangle(double base, double height) const override;
};

}  // namespace shapes_strategy
