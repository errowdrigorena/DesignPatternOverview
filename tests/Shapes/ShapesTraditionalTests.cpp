#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ios>
#include <iostream>
#include <numbers>
#include <sstream>

namespace {

using shapes_traditional::Circle;
using shapes_traditional::Rectangle;
using shapes_traditional::Triangle;
using testing::DoubleNear;

constexpr double tolerance = 1e-9;

class CapturedStdout {
public:
    CapturedStdout()
        : previous_buffer_{std::cout.rdbuf(output_.rdbuf())}
    {
    }

    ~CapturedStdout()
    {
        std::cout.rdbuf(previous_buffer_);
    }

    [[nodiscard]] std::string str() const
    {
        return output_.str();
    }

private:
    std::ostringstream output_;
    std::streambuf* previous_buffer_;
};

TEST(TraditionalShapes, CalculateAreas)
{
    const Circle circle{3.0};
    const Rectangle rectangle{4.0, 2.5};
    const Triangle triangle{6.0, 3.0};

    EXPECT_THAT(circle.calculate_area(), DoubleNear(std::numbers::pi_v<double> * 9.0, tolerance));
    EXPECT_DOUBLE_EQ(rectangle.calculate_area(), 10.0);
    EXPECT_DOUBLE_EQ(triangle.calculate_area(), 9.0);
}

TEST(TraditionalShapes, FactoryFunctionsCreatePolymorphicShapes)
{
    const auto circle = Circle::create(3.0);
    const auto rectangle = Rectangle::create(4.0, 2.5);
    const auto triangle = Triangle::create(6.0, 3.0);

    EXPECT_THAT(circle->calculate_area(), DoubleNear(std::numbers::pi_v<double> * 9.0, tolerance));
    EXPECT_DOUBLE_EQ(rectangle->calculate_area(), 10.0);
    EXPECT_DOUBLE_EQ(triangle->calculate_area(), 9.0);
}

TEST(TraditionalShapes, DrawWritesShapeDescriptions)
{
    CapturedStdout output;

    Circle{2.0}.draw();
    Rectangle{4.0, 2.5}.draw();
    Triangle{6.0, 3.0}.draw();

    EXPECT_EQ(
        output.str(),
        "Drawing a circle with radius 2\n"
        "Drawing a rectangle with width 4 and height 2.5\n"
        "Drawing a triangle with base 6 and height 3\n");
}

}  // namespace
