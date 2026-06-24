#include <Shapes_strategy_classic/Shape.hpp>

#include <stdexcept>
#include <utility>

namespace shapes_strategy {

Shape::Shape(std::unique_ptr<DrawStrategy> draw_strategy)
    : draw_strategy_{std::move(draw_strategy)}
{
    if (!draw_strategy_) {
        throw std::invalid_argument{"draw_strategy cannot be null"};
    }
}

void Shape::set_strategy(std::unique_ptr<DrawStrategy> draw_strategy)
{
    if (!draw_strategy) {
        throw std::invalid_argument{"draw_strategy cannot be null"};
    }

    draw_strategy_ = std::move(draw_strategy);
}

}  // namespace shapes_strategy
