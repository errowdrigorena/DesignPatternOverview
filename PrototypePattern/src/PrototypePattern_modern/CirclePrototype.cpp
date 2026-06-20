#include <PrototypePattern_modern/CirclePrototype.hpp>

#include <ostream>
#include <utility>

namespace prototype_pattern_modern {

CirclePrototype::CirclePrototype(
    std::string name,
    std::string color,
    const double x,
    const double y,
    const double radius)
    : name_{std::move(name)}
    , color_{std::move(color)}
    , x_{x}
    , y_{y}
    , radius_{radius}
{
}

void CirclePrototype::set_name(std::string name)
{
    name_ = std::move(name);
}

void CirclePrototype::set_color(std::string color)
{
    color_ = std::move(color);
}

void CirclePrototype::move_to(const double x, const double y)
{
    x_ = x;
    y_ = y;
}

void CirclePrototype::draw(std::ostream& output) const
{
    output << "CirclePrototype{name=" << name_
           << ", color=" << color_
           << ", x=" << x_
           << ", y=" << y_
           << ", radius=" << radius_
           << "}\n";
}

}  // namespace prototype_pattern_modern
