#include <Shapes_modern/Triangle.hpp>

#include <iostream>

namespace shapes_modern {

Triangle::Triangle(const double base, const double height)
    : base_{base}
    , height_{height}
{
}

void Triangle::draw() const
{
    std::cout << "Drawing a triangle with base " << base_
              << " and height " << height_ << '\n';
}

double Triangle::calculate_area() const
{
    return base_ * height_ / 2.0;
}

}  // namespace shapes_modern
