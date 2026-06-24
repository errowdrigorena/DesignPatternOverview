#include <Shapes_traditional/Circle.hpp>

#include <iostream>
#include <memory>
#include <numbers>

namespace shapes_traditional {

Circle::Circle(const double radius)
    : radius_{radius}
{
}

void Circle::draw() const
{
    std::cout << "Drawing a circle with radius " << radius_ << '\n';
}

double Circle::calculate_area() const
{
    return std::numbers::pi_v<double> * radius_ * radius_;
}

std::unique_ptr<Shape> Circle::create(const double radius)
{
    return std::make_unique<Circle>(radius);
}

}  // namespace shapes_traditional
