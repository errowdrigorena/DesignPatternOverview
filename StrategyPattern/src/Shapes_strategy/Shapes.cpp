#include <Shapes_strategy/Shapes.hpp>

#include <stdexcept>
#include <utility>

namespace shapes_strategy {

Shapes::Shapes(std::unique_ptr<DrawStrategy> draw_strategy)
    : draw_strategy_{std::move(draw_strategy)}
{
    if (!draw_strategy_) {
        throw std::invalid_argument{"draw_strategy cannot be null"};
    }
}

void Shapes::set_strategy(std::unique_ptr<DrawStrategy> draw_strategy)
{
    if (!draw_strategy) {
        throw std::invalid_argument{"draw_strategy cannot be null"};
    }

    draw_strategy_ = std::move(draw_strategy);
}

}  // namespace shapes_strategy
