#include <Shapes_strategy_function/Circle.hpp>

#include <numbers>
#include <stdexcept>
#include <utility>

namespace shapes_strategy_function {

Circle::Circle(const double radius, DrawStrategy draw_strategy)
    : radius_{radius}
    , draw_strategy_{std::move(draw_strategy)}
{
    if (!draw_strategy_) {
        throw std::invalid_argument{"draw_strategy cannot be empty"};
    }
}

void Circle::draw() const
{
    draw_strategy_(*this);
}

double Circle::calculate_area() const
{
    return std::numbers::pi_v<double> * radius_ * radius_;
}

void Circle::set_strategy(DrawStrategy draw_strategy)
{
    if (!draw_strategy) {
        throw std::invalid_argument{"draw_strategy cannot be empty"};
    }

    draw_strategy_ = std::move(draw_strategy);
}

double Circle::radius() const
{
    return radius_;
}

}  // namespace shapes_strategy_function
