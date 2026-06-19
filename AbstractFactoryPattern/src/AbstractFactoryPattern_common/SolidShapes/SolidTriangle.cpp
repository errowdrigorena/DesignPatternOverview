#include <AbstractFactoryPattern_common/SolidShapes/SolidTriangle.hpp>

#include <iostream>

namespace abstract_factory_pattern_common {

SolidTriangle::SolidTriangle(const double base, const double height)
    : base_{base}
    , height_{height}
{
}

void SolidTriangle::draw() const
{
    std::cout << "Solid triangle\n";
}

double SolidTriangle::calculate_area() const
{
    return base_ * height_ / 2.0;
}

std::string_view SolidTriangle::family() const
{
    return "solid";
}

}  // namespace abstract_factory_pattern_common
