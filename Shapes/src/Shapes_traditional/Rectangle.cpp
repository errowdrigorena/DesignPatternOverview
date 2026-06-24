#include <Shapes_traditional/Rectangle.hpp>

#include <iostream>
#include <memory>

namespace shapes_traditional {

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

std::unique_ptr<Shape> Rectangle::create(const double width, const double height)
{
    return std::make_unique<Rectangle>(width, height);
}

}  // namespace shapes_traditional
