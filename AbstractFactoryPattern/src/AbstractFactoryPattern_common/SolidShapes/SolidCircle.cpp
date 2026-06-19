#include <AbstractFactoryPattern_common/SolidShapes/SolidCircle.hpp>

#include <iostream>
#include <numbers>

namespace abstract_factory_pattern_common {

SolidCircle::SolidCircle(const double radius)
    : radius_{radius}
{
}

void SolidCircle::draw() const
{
    std::cout << "Solid circle\n";
}

double SolidCircle::calculate_area() const
{
    return std::numbers::pi_v<double> * radius_ * radius_;
}

std::string_view SolidCircle::family() const
{
    return "solid";
}

}  // namespace abstract_factory_pattern_common
