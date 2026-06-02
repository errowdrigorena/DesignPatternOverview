#include <VisitorPattern_classic/Rectangle.hpp>

#include <VisitorPattern_classic/ShapeVisitor.hpp>

namespace visitor_pattern_classic {

Rectangle::Rectangle(const double width, const double height)
    : width_{width}
    , height_{height}
{
}

double Rectangle::width() const
{
    return width_;
}

double Rectangle::height() const
{
    return height_;
}

void Rectangle::accept(ShapeVisitor& visitor) const
{
    visitor.visit(*this);
}

}  // namespace visitor_pattern_classic
