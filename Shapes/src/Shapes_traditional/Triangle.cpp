#include <Shapes_traditional/Triangle.hpp>

#include <iostream>
#include <memory>

namespace shapes_traditional {

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

std::unique_ptr<Shapes> Triangle::create(const double base, const double height)
{
    return std::make_unique<Triangle>(base, height);
}

}  // namespace shapes_traditional
