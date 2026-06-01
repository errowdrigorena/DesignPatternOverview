#include <Shapes_strategy/Triangle_strategy.hpp>

#include <utility>

namespace shapes_strategy {

Triangle_strategy::Triangle_strategy(
    const double base,
    const double height,
    std::unique_ptr<DrawStrategy> draw_strategy)
    : Shapes{std::move(draw_strategy)}
    , base_{base}
    , height_{height}
{
}

void Triangle_strategy::draw() const
{
    draw_strategy_->draw_triangle(base_, height_);
}

double Triangle_strategy::calculate_area() const
{
    return base_ * height_ / 2.0;
}

}  // namespace shapes_strategy
