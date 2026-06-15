#include <VisitorPattern_classic/AreaVisitor.hpp>

#include <VisitorPattern_classic/Circle.hpp>
#include <VisitorPattern_classic/Rectangle.hpp>
#include <VisitorPattern_classic/Triangle.hpp>

#include <numbers>

namespace visitor_pattern_classic {

void AreaVisitor::visit(const Circle& circle)
{
    area_ = std::numbers::pi_v<double> * circle.radius() * circle.radius();
}

void AreaVisitor::visit(const Rectangle& rectangle)
{
    area_ = rectangle.width() * rectangle.height();
}

void AreaVisitor::visit(const Triangle& triangle)
{
    area_ = triangle.base() * triangle.height() / 2.0;
}

double AreaVisitor::area() const
{
    return area_;
}

}  // namespace visitor_pattern_classic
