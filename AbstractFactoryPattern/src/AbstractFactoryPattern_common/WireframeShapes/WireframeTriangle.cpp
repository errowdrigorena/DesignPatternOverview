#include <AbstractFactoryPattern_common/WireframeShapes/WireframeTriangle.hpp>

#include <iostream>

namespace abstract_factory_pattern_common {

WireframeTriangle::WireframeTriangle(const double base, const double height)
    : base_{base}
    , height_{height}
{
}

void WireframeTriangle::draw() const
{
    std::cout << "Wireframe triangle\n";
}

double WireframeTriangle::calculate_area() const
{
    return base_ * height_ / 2.0;
}

std::string_view WireframeTriangle::family() const
{
    return "wireframe";
}

}  // namespace abstract_factory_pattern_common
