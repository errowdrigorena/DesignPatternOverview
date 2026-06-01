#include <Shapes_strategy_function/Triangle.hpp>

#include <stdexcept>
#include <utility>

namespace shapes_strategy_function {

Triangle::Triangle(const double base, const double height, DrawStrategy draw_strategy)
    : base_{base}
    , height_{height}
    , draw_strategy_{std::move(draw_strategy)}
{
    if (!draw_strategy_) {
        throw std::invalid_argument{"draw_strategy cannot be empty"};
    }
}

void Triangle::draw() const
{
    draw_strategy_(*this);
}

double Triangle::calculate_area() const
{
    return base_ * height_ / 2.0;
}

void Triangle::set_strategy(DrawStrategy draw_strategy)
{
    if (!draw_strategy) {
        throw std::invalid_argument{"draw_strategy cannot be empty"};
    }

    draw_strategy_ = std::move(draw_strategy);
}

double Triangle::base() const
{
    return base_;
}

double Triangle::height() const
{
    return height_;
}

}  // namespace shapes_strategy_function
