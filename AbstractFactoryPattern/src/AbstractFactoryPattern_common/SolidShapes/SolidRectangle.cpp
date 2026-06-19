#include <AbstractFactoryPattern_common/SolidShapes/SolidRectangle.hpp>

#include <iostream>

namespace abstract_factory_pattern_common {

SolidRectangle::SolidRectangle(const double width, const double height)
    : width_{width}
    , height_{height}
{
}

void SolidRectangle::draw() const
{
    std::cout << "Solid rectangle\n";
}

double SolidRectangle::calculate_area() const
{
    return width_ * height_;
}

std::string_view SolidRectangle::family() const
{
    return "solid";
}

}  // namespace abstract_factory_pattern_common
