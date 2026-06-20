#include <BuilderPattern_common/Rectangle.hpp>

#include <utility>

namespace builder_pattern_common {

Rectangle::Rectangle(std::string name, const double width, const double height)
    : name_{std::move(name)}
    , width_{width}
    , height_{height}
{
}

std::string_view Rectangle::name() const
{
    return name_;
}

double Rectangle::width() const
{
    return width_;
}

double Rectangle::height() const
{
    return height_;
}

double Rectangle::area() const
{
    return width_ * height_;
}

}  // namespace builder_pattern_common
