#pragma once

#include <VisitorPattern_modern/Shape.hpp>

#include <numbers>

namespace visitor_pattern_modern {

struct AreaVisitor {
    [[nodiscard]] double operator()(const Circle& circle) const
    {
        return std::numbers::pi * circle.radius * circle.radius;
    }

    [[nodiscard]] double operator()(const Rectangle& rectangle) const
    {
        return rectangle.width * rectangle.height;
    }

    [[nodiscard]] double operator()(const Triangle& triangle) const
    {
        return triangle.base * triangle.height / 2.0;
    }
};

}  // namespace visitor_pattern_modern
