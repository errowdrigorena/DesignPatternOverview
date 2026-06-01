#include <Shapes_strategy/ApiDrawStrategy.hpp>

#include <iostream>

namespace shapes_strategy {

void ApiDrawStrategy::draw_circle(const double radius) const
{
    std::cout << "Circle with radius " << radius << " has been sent to the API\n";
}

void ApiDrawStrategy::draw_rectangle(const double width, const double height) const
{
    std::cout << "Rectangle with width " << width << " and height " << height
              << " has been sent to the API\n";
}

void ApiDrawStrategy::draw_triangle(const double base, const double height) const
{
    std::cout << "Triangle with base " << base << " and height " << height
              << " has been sent to the API\n";
}

}  // namespace shapes_strategy
