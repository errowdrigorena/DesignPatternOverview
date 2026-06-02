#include <VisitorPattern_classic/Triangle.hpp>

#include <VisitorPattern_classic/ShapeVisitor.hpp>

namespace visitor_pattern_classic {

Triangle::Triangle(const double base, const double height)
    : base_{base}
    , height_{height}
{
}

double Triangle::base() const
{
    return base_;
}

double Triangle::height() const
{
    return height_;
}

void Triangle::accept(ShapeVisitor& visitor) const
{
    visitor.visit(*this);
}

}  // namespace visitor_pattern_classic
