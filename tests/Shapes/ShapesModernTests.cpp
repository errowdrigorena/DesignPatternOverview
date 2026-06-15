#include <Shapes_modern/Circle.hpp>
#include <Shapes_modern/Rectangle.hpp>
#include <Shapes_modern/Triangle.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ios>
#include <iostream>
#include <numbers>
#include <sstream>

namespace {

using shapes_modern::Circle;
using shapes_modern::Rectangle;
using shapes_modern::Triangle;
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

TEST(ModernShapes, CalculateAreas)
{
    const Circle circle{3.0};
    const Rectangle rectangle{4.0, 2.5};
    const Triangle triangle{6.0, 3.0};

    EXPECT_THAT(circle.calculate_area(), DoubleNear(std::numbers::pi_v<double> * 9.0, tolerance));
    EXPECT_DOUBLE_EQ(rectangle.calculate_area(), 10.0);
    EXPECT_DOUBLE_EQ(triangle.calculate_area(), 9.0);
}

TEST(ModernShapes, DrawWritesShapeDescriptions)
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
