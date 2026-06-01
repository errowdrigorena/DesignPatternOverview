#pragma once

namespace shapes_strategy {

class DrawStrategy {
public:
    virtual ~DrawStrategy() = default;

    virtual void draw_circle(double radius) const = 0;
    virtual void draw_rectangle(double width, double height) const = 0;
    virtual void draw_triangle(double base, double height) const = 0;
};

}  // namespace shapes_strategy
