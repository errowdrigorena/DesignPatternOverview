#include <BridgePattern_modern/Shape.hpp>

#include <stdexcept>
#include <utility>

namespace bridge_pattern_modern {

Shape::Shape(std::string name, bridge_pattern_common::ShapePath path, Renderer renderer)
    : name_{std::move(name)}
    , path_{std::move(path)}
    , renderer_{std::move(renderer)}
{
    if (!renderer_) {
        throw std::invalid_argument("A shape requires a renderer");
    }
}

Shape Shape::rectangle(const double width, const double height, Renderer renderer)
{
    return Shape{"rectangle", {{0.0, 0.0}, {width, 0.0}, {width, height}, {0.0, height}}, std::move(renderer)};
}

Shape Shape::triangle(const double base, const double height, Renderer renderer)
{
    return Shape{"triangle", {{0.0, height}, {base / 2.0, 0.0}, {base, height}}, std::move(renderer)};
}

void Shape::set_renderer(Renderer renderer)
{
    if (!renderer) {
        throw std::invalid_argument("A shape requires a renderer");
    }

    renderer_ = std::move(renderer);
}

void Shape::draw() const
{
    renderer_(name_, path_);
}

}  // namespace bridge_pattern_modern
