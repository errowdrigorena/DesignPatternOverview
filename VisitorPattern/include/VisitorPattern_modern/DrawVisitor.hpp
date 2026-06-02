#pragma once

#include <VisitorPattern_modern/Shape.hpp>

#include <ostream>

namespace visitor_pattern_modern {

class DrawVisitor {
public:
    explicit DrawVisitor(std::ostream& output)
        : output_{output}
    {
    }

    void operator()(const Circle& circle) const
    {
        output_ << "Drawing a circle with radius " << circle.radius << '\n';
    }

    void operator()(const Rectangle& rectangle) const
    {
        output_ << "Drawing a rectangle with width " << rectangle.width
                << " and height " << rectangle.height << '\n';
    }

    void operator()(const Triangle& triangle) const
    {
        output_ << "Drawing a triangle with base " << triangle.base
                << " and height " << triangle.height << '\n';
    }

private:
    std::ostream& output_;
};

}  // namespace visitor_pattern_modern
