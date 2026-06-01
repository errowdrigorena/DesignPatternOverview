#include <Shapes_strategy/StarDrawStrategy.hpp>

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
    std::cout << "Circle with radius " << radius << '\n';
    std::cout << " *** \n";
    std::cout << "*   *\n";
    std::cout << "*   *\n";
    std::cout << " *** \n";
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
