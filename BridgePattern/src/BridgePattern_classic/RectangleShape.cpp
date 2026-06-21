#include <BridgePattern_classic/RectangleShape.hpp>

#include <utility>

namespace bridge_pattern_classic {

RectangleShape::RectangleShape(const double width,
                               const double height,
                               std::shared_ptr<const ShapeRenderer> renderer)
    : Shape{std::move(renderer)}
    , width_{width}
    , height_{height}
{
}

std::string_view RectangleShape::name() const
{
    return "rectangle";
}

bridge_pattern_common::ShapePath RectangleShape::outline() const
{
    return {{0.0, 0.0}, {width_, 0.0}, {width_, height_}, {0.0, height_}};
}

}  // namespace bridge_pattern_classic
