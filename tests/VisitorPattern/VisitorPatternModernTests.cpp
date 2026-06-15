#include <VisitorPattern_modern/AreaVisitor.hpp>
#include <VisitorPattern_modern/DrawVisitor.hpp>
#include <VisitorPattern_modern/Shape.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <sstream>
#include <variant>
#include <vector>

namespace {

using testing::DoubleNear;
using visitor_pattern_modern::AreaVisitor;
using visitor_pattern_modern::Circle;
using visitor_pattern_modern::DrawVisitor;
using visitor_pattern_modern::Rectangle;
using visitor_pattern_modern::Shape;
using visitor_pattern_modern::Triangle;

constexpr double tolerance = 1e-9;

TEST(ModernAreaVisitor, CalculatesAreaForEveryShapeVariant)
{
    const std::vector<Shape> shapes{
        Circle{3.0},
        Rectangle{4.0, 2.5},
        Triangle{6.0, 3.0},
    };
    const AreaVisitor visitor;

    EXPECT_THAT(std::visit(visitor, shapes[0]), DoubleNear(std::numbers::pi_v<double> * 9.0, tolerance));
    EXPECT_DOUBLE_EQ(std::visit(visitor, shapes[1]), 10.0);
    EXPECT_DOUBLE_EQ(std::visit(visitor, shapes[2]), 9.0);
}

TEST(ModernDrawVisitor, WritesDescriptionsForEveryShapeVariant)
{
    const std::vector<Shape> shapes{
        Circle{2.0},
        Rectangle{4.0, 2.5},
        Triangle{6.0, 3.0},
    };
    std::ostringstream output;
    const DrawVisitor visitor{output};

    for (const auto& shape : shapes) {
        std::visit(visitor, shape);
    }

    EXPECT_EQ(
        output.str(),
        "Drawing a circle with radius 2\n"
        "Drawing a rectangle with width 4 and height 2.5\n"
        "Drawing a triangle with base 6 and height 3\n");
}

}  // namespace
