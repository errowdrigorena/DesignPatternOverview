#include <BridgePattern_classic/Shape.hpp>

#include <stdexcept>
#include <utility>

namespace bridge_pattern_classic {

Shape::Shape(std::shared_ptr<const ShapeRenderer> renderer)
    : renderer_{std::move(renderer)}
{
    if (!renderer_) {
        throw std::invalid_argument("A shape requires a renderer");
    }
}

void Shape::set_renderer(std::shared_ptr<const ShapeRenderer> renderer)
{
    if (!renderer) {
        throw std::invalid_argument("A shape requires a renderer");
    }

    renderer_ = std::move(renderer);
}

void Shape::draw() const
{
    renderer_->render(name(), outline());
}

}  // namespace bridge_pattern_classic
