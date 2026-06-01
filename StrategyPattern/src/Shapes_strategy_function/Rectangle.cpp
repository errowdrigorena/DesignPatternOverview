#include <Shapes_strategy_function/Rectangle.hpp>

#include <stdexcept>
#include <utility>

namespace shapes_strategy_function {

Rectangle::Rectangle(const double width, const double height, DrawStrategy draw_strategy)
    : width_{width}
    , height_{height}
    , draw_strategy_{std::move(draw_strategy)}
{
    if (!draw_strategy_) {
        throw std::invalid_argument{"draw_strategy cannot be empty"};
    }
}

void Rectangle::draw() const
{
    draw_strategy_(*this);
}

double Rectangle::calculate_area() const
{
    return width_ * height_;
}

void Rectangle::set_strategy(DrawStrategy draw_strategy)
{
    if (!draw_strategy) {
        throw std::invalid_argument{"draw_strategy cannot be empty"};
    }

    draw_strategy_ = std::move(draw_strategy);
}

double Rectangle::width() const
{
    return width_;
}

double Rectangle::height() const
{
    return height_;
}

}  // namespace shapes_strategy_function
