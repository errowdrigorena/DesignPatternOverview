#include <BridgePattern_classic/TriangleShape.hpp>

#include <utility>

namespace bridge_pattern_classic {

TriangleShape::TriangleShape(const double base,
                             const double height,
                             std::shared_ptr<const ShapeRenderer> renderer)
    : Shape{std::move(renderer)}
    , base_{base}
    , height_{height}
{
}

std::string_view TriangleShape::name() const
{
    return "triangle";
}

bridge_pattern_common::ShapePath TriangleShape::outline() const
{
    return {{0.0, height_}, {base_ / 2.0, 0.0}, {base_, height_}};
}

}  // namespace bridge_pattern_classic
