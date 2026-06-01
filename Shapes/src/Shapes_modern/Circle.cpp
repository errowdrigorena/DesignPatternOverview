#include <Shapes_modern/Circle.hpp>

#include <iostream>
#include <numbers>

namespace shapes_modern {

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

}  // namespace shapes_modern
