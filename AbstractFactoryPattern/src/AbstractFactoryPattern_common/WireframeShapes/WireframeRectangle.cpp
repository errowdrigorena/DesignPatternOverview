#include <AbstractFactoryPattern_common/WireframeShapes/WireframeRectangle.hpp>

#include <iostream>

namespace abstract_factory_pattern_common {

WireframeRectangle::WireframeRectangle(const double width, const double height)
    : width_{width}
    , height_{height}
{
}

void WireframeRectangle::draw() const
{
    std::cout << "Wireframe rectangle\n";
}

double WireframeRectangle::calculate_area() const
{
    return width_ * height_;
}

std::string_view WireframeRectangle::family() const
{
    return "wireframe";
}

}  // namespace abstract_factory_pattern_common
