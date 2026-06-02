#include <VisitorPattern_classic/DrawVisitor.hpp>

#include <VisitorPattern_classic/Circle.hpp>
#include <VisitorPattern_classic/Rectangle.hpp>
#include <VisitorPattern_classic/Triangle.hpp>

#include <ostream>

namespace visitor_pattern_classic {

DrawVisitor::DrawVisitor(std::ostream& output)
    : output_{output}
{
}

void DrawVisitor::visit(const Circle& circle)
{
    output_ << "Drawing a circle with radius " << circle.radius() << '\n';
}

void DrawVisitor::visit(const Rectangle& rectangle)
{
    output_ << "Drawing a rectangle with width " << rectangle.width()
            << " and height " << rectangle.height() << '\n';
}

void DrawVisitor::visit(const Triangle& triangle)
{
    output_ << "Drawing a triangle with base " << triangle.base()
            << " and height " << triangle.height() << '\n';
}

}  // namespace visitor_pattern_classic
