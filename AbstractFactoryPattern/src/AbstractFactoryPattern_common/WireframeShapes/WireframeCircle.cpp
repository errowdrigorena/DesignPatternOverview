#include <AbstractFactoryPattern_common/WireframeShapes/WireframeCircle.hpp>

#include <iostream>
#include <numbers>

namespace abstract_factory_pattern_common {

WireframeCircle::WireframeCircle(const double radius)
    : radius_{radius}
{
}

void WireframeCircle::draw() const
{
    std::cout << "Wireframe circle\n";
}

double WireframeCircle::calculate_area() const
{
    return std::numbers::pi_v<double> * radius_ * radius_;
}

std::string_view WireframeCircle::family() const
{
    return "wireframe";
}

}  // namespace abstract_factory_pattern_common
