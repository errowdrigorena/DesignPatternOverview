#include <Shapes_strategy_classic/StarDrawStrategy.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

namespace shapes_strategy {
namespace {

[[nodiscard]] int rounded_dimension(const double value)
{
    return std::max(2, static_cast<int>(std::lround(value)));
}

}  // namespace

void StarDrawStrategy::draw_circle(const double radius) const
{
    const auto rounded_radius = rounded_dimension(radius);

    std::cout << "Circle with radius " << radius << '\n';

    for (auto row = -rounded_radius; row <= rounded_radius; ++row) {
        for (auto column = -rounded_radius; column <= rounded_radius; ++column) {
            const auto distance_from_center = row * row + column * column;
            const auto circle_radius = rounded_radius * rounded_radius;
            std::cout << (distance_from_center <= circle_radius ? '*' : ' ');
        }

        std::cout << '\n';
    }
}

void StarDrawStrategy::draw_rectangle(const double width, const double height) const
{
    const auto columns = rounded_dimension(width);
    const auto rows = rounded_dimension(height);

    std::cout << "Rectangle with width " << width << " and height " << height << '\n';

    for (auto row = 0; row < rows; ++row) {
        for (auto column = 0; column < columns; ++column) {
            std::cout << '*';
        }

        std::cout << '\n';
    }
}

void StarDrawStrategy::draw_triangle(const double base, const double height) const
{
    const auto rows = rounded_dimension(height);

    std::cout << "Triangle with base " << base << " and height " << height << '\n';

    for (auto row = 1; row <= rows; ++row) {
        for (auto column = 0; column < row; ++column) {
            std::cout << '*';
        }

        std::cout << '\n';
    }
}

}  // namespace shapes_strategy
