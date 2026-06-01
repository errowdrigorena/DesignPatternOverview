#include <Shapes_strategy_classic/Rectangle_strategy.hpp>

#include <utility>

namespace shapes_strategy {

Rectangle_strategy::Rectangle_strategy(
    const double width,
    const double height,
    std::unique_ptr<DrawStrategy> draw_strategy)
    : Shapes{std::move(draw_strategy)}
    , width_{width}
    , height_{height}
{
}

void Rectangle_strategy::draw() const
{
    draw_strategy_->draw_rectangle(width_, height_);
}

double Rectangle_strategy::calculate_area() const
{
    return width_ * height_;
}

}  // namespace shapes_strategy
