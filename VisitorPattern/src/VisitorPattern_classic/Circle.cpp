#include <VisitorPattern_classic/Circle.hpp>

#include <VisitorPattern_classic/ShapeVisitor.hpp>

namespace visitor_pattern_classic {

Circle::Circle(const double radius)
    : radius_{radius}
{
}

double Circle::radius() const
{
    return radius_;
}

void Circle::accept(ShapeVisitor& visitor) const
{
    visitor.visit(*this);
}

}  // namespace visitor_pattern_classic
