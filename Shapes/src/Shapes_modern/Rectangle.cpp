#include <Shapes_modern/Rectangle.hpp>

#include <iostream>

namespace shapes_modern {

Rectangle::Rectangle(const double width, const double height)
    : width_{width}
    , height_{height}
{
}

void Rectangle::draw() const
{
    std::cout << "Drawing a rectangle with width " << width_
              << " and height " << height_ << '\n';
}

double Rectangle::calculate_area() const
{
    return width_ * height_;
}

}  // namespace shapes_modern
