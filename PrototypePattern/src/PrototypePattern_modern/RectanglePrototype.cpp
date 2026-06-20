#include <PrototypePattern_modern/RectanglePrototype.hpp>

#include <ostream>
#include <utility>

namespace prototype_pattern_modern {

RectanglePrototype::RectanglePrototype(
    std::string name,
    std::string color,
    const double x,
    const double y,
    const double width,
    const double height)
    : name_{std::move(name)}
    , color_{std::move(color)}
    , x_{x}
    , y_{y}
    , width_{width}
    , height_{height}
{
}

void RectanglePrototype::set_name(std::string name)
{
    name_ = std::move(name);
}

void RectanglePrototype::set_color(std::string color)
{
    color_ = std::move(color);
}

void RectanglePrototype::move_to(const double x, const double y)
{
    x_ = x;
    y_ = y;
}

void RectanglePrototype::draw(std::ostream& output) const
{
    output << "RectanglePrototype{name=" << name_
           << ", color=" << color_
           << ", x=" << x_
           << ", y=" << y_
           << ", width=" << width_
           << ", height=" << height_
           << "}\n";
}

}  // namespace prototype_pattern_modern
