#include <Shapes_strategy_function/DrawStrategies.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

namespace shapes_strategy_function {
namespace {

[[nodiscard]] int rounded_dimension(const double value)
{
    return std::max(2, static_cast<int>(std::lround(value)));
}

}  // namespace

void draw_circle_with_stars(Circle const& circle)
{
    const auto rounded_radius = rounded_dimension(circle.radius());

    std::cout << "Circle with radius " << circle.radius() << '\n';

    for (auto row = -rounded_radius; row <= rounded_radius; ++row) {
        for (auto column = -rounded_radius; column <= rounded_radius; ++column) {
            const auto distance_from_center = row * row + column * column;
            const auto circle_radius = rounded_radius * rounded_radius;
            std::cout << (distance_from_center <= circle_radius ? '*' : ' ');
        }

        std::cout << '\n';
    }
}

void draw_rectangle_with_stars(Rectangle const& rectangle)
{
    const auto columns = rounded_dimension(rectangle.width());
    const auto rows = rounded_dimension(rectangle.height());

    std::cout << "Rectangle with width " << rectangle.width()
              << " and height " << rectangle.height() << '\n';

    for (auto row = 0; row < rows; ++row) {
        for (auto column = 0; column < columns; ++column) {
            std::cout << '*';
        }

        std::cout << '\n';
    }
}

void draw_triangle_with_stars(Triangle const& triangle)
{
    const auto rows = rounded_dimension(triangle.height());

    std::cout << "Triangle with base " << triangle.base()
              << " and height " << triangle.height() << '\n';

    for (auto row = 1; row <= rows; ++row) {
        for (auto column = 0; column < row; ++column) {
            std::cout << '*';
        }

        std::cout << '\n';
    }
}

void send_circle_to_api(Circle const& circle)
{
    std::cout << "Circle with radius " << circle.radius() << " has been sent to the API\n";
}

void send_rectangle_to_api(Rectangle const& rectangle)
{
    std::cout << "Rectangle with width " << rectangle.width()
              << " and height " << rectangle.height() << " has been sent to the API\n";
}

void send_triangle_to_api(Triangle const& triangle)
{
    std::cout << "Triangle with base " << triangle.base()
              << " and height " << triangle.height() << " has been sent to the API\n";
}

}  // namespace shapes_strategy_function
