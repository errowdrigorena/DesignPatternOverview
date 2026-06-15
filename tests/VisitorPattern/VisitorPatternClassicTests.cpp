#include <VisitorPattern_classic/AreaVisitor.hpp>
#include <VisitorPattern_classic/Circle.hpp>
#include <VisitorPattern_classic/DrawVisitor.hpp>
#include <VisitorPattern_classic/Rectangle.hpp>
#include <VisitorPattern_classic/ShapeVisitor.hpp>
#include <VisitorPattern_classic/Triangle.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <sstream>
#include <string>

namespace {

using testing::DoubleNear;
using visitor_pattern_classic::AreaVisitor;
using visitor_pattern_classic::Circle;
using visitor_pattern_classic::DrawVisitor;
using visitor_pattern_classic::Rectangle;
using visitor_pattern_classic::ShapeVisitor;
using visitor_pattern_classic::Triangle;

constexpr double tolerance = 1e-9;

class RecordingVisitor final : public ShapeVisitor {
public:
    void visit(const Circle&) override
    {
        visited_shape = "circle";
    }

    void visit(const Rectangle&) override
    {
        visited_shape = "rectangle";
    }

    void visit(const Triangle&) override
    {
        visited_shape = "triangle";
    }

    std::string visited_shape;
};

TEST(ClassicVisitorShapes, ExposeTheirDimensions)
{
    const Circle circle{3.0};
    const Rectangle rectangle{4.0, 2.5};
    const Triangle triangle{6.0, 3.0};

    EXPECT_DOUBLE_EQ(circle.radius(), 3.0);
    EXPECT_DOUBLE_EQ(rectangle.width(), 4.0);
    EXPECT_DOUBLE_EQ(rectangle.height(), 2.5);
    EXPECT_DOUBLE_EQ(triangle.base(), 6.0);
    EXPECT_DOUBLE_EQ(triangle.height(), 3.0);
}

TEST(ClassicVisitorShapes, AcceptDispatchesToMatchingVisitOverload)
{
    RecordingVisitor visitor;

    Circle{1.0}.accept(visitor);
    EXPECT_EQ(visitor.visited_shape, "circle");

    Rectangle{2.0, 3.0}.accept(visitor);
    EXPECT_EQ(visitor.visited_shape, "rectangle");

    Triangle{4.0, 5.0}.accept(visitor);
    EXPECT_EQ(visitor.visited_shape, "triangle");
}

TEST(ClassicAreaVisitor, CalculatesCircleArea)
{
    AreaVisitor visitor;

    Circle{3.0}.accept(visitor);

    EXPECT_THAT(visitor.area(), DoubleNear(std::numbers::pi_v<double> * 9.0, tolerance));
}

TEST(ClassicAreaVisitor, CalculatesRectangleArea)
{
    AreaVisitor visitor;

    Rectangle{4.0, 2.5}.accept(visitor);

    EXPECT_DOUBLE_EQ(visitor.area(), 10.0);
}

TEST(ClassicAreaVisitor, CalculatesTriangleArea)
{
    AreaVisitor visitor;

    Triangle{6.0, 3.0}.accept(visitor);

    EXPECT_DOUBLE_EQ(visitor.area(), 9.0);
}

TEST(ClassicDrawVisitor, WritesShapeDescriptions)
{
    std::ostringstream output;
    DrawVisitor visitor{output};

    Circle{2.0}.accept(visitor);
    Rectangle{4.0, 2.5}.accept(visitor);
    Triangle{6.0, 3.0}.accept(visitor);

    EXPECT_EQ(
        output.str(),
        "Drawing a circle with radius 2\n"
        "Drawing a rectangle with width 4 and height 2.5\n"
        "Drawing a triangle with base 6 and height 3\n");
}

}  // namespace
