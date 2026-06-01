#include <Shapes_strategy/Circle_strategy.hpp>

#include <numbers>
#include <utility>

namespace shapes_strategy {

Circle_strategy::Circle_strategy(
    const double radius,
    std::unique_ptr<DrawStrategy> draw_strategy)
    : Shapes{std::move(draw_strategy)}
    , radius_{radius}
{
}

void Circle_strategy::draw() const
{
    draw_strategy_->draw_circle(radius_);
}

double Circle_strategy::calculate_area() const
{
    return std::numbers::pi_v<double> * radius_ * radius_;
}

}  // namespace shapes_strategy
