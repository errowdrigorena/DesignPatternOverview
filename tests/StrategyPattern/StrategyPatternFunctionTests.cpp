#include <Shapes_strategy_function/Circle.hpp>
#include <Shapes_strategy_function/DrawStrategies.hpp>
#include <Shapes_strategy_function/Rectangle.hpp>
#include <Shapes_strategy_function/Triangle.hpp>
#include <TestDoubles/Spies/DrawCall.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

using shapes_strategy_function::Circle;
using shapes_strategy_function::Rectangle;
using shapes_strategy_function::Triangle;
using test_doubles::spies::DrawCall;
using test_doubles::spies::expect_draw_call;
using testing::DoubleNear;
using testing::ElementsAre;
using testing::HasSubstr;
using testing::Throws;

constexpr double tolerance = 1e-9;

class CoutCapture {
public:
    CoutCapture()
        : old_buffer_{std::cout.rdbuf(output_.rdbuf())}
    {
    }

    ~CoutCapture()
    {
        std::cout.rdbuf(old_buffer_);
    }

    [[nodiscard]] std::string str() const
    {
        return output_.str();
    }

private:
    std::ostringstream output_;
    std::streambuf* old_buffer_;
};

TEST(FunctionStrategyCircle, ExposesRadiusAndCalculatesArea)
{
    const Circle circle{3.0, [](Circle const&) {}};

    EXPECT_THAT(circle.radius(), DoubleNear(3.0, tolerance));
    EXPECT_THAT(circle.calculate_area(), DoubleNear(std::numbers::pi_v<double> * 9.0, tolerance));
}

TEST(FunctionStrategyCircle, DrawDelegatesToCurrentCallable)
{
    std::vector<DrawCall> calls;
    const Circle circle{2.5, [&calls](Circle const& shape) {
                            calls.push_back({"circle", shape.radius(), std::nullopt});
                        }};

    circle.draw();

    ASSERT_EQ(calls.size(), 1);
    expect_draw_call(calls.front(), "circle", 2.5, std::nullopt);
}

TEST(FunctionStrategyRectangle, ExposesDimensionsAndCalculatesArea)
{
    const Rectangle rectangle{4.0, 2.5, [](Rectangle const&) {}};

    EXPECT_THAT(rectangle.width(), DoubleNear(4.0, tolerance));
    EXPECT_THAT(rectangle.height(), DoubleNear(2.5, tolerance));
    EXPECT_THAT(rectangle.calculate_area(), DoubleNear(10.0, tolerance));
}

TEST(FunctionStrategyRectangle, DrawDelegatesToCurrentCallable)
{
    std::vector<DrawCall> calls;
    const Rectangle rectangle{4.0, 2.5, [&calls](Rectangle const& shape) {
                                  calls.push_back({"rectangle", shape.width(), shape.height()});
                              }};

    rectangle.draw();

    ASSERT_EQ(calls.size(), 1);
    expect_draw_call(calls.front(), "rectangle", 4.0, 2.5);
}

TEST(FunctionStrategyTriangle, ExposesDimensionsAndCalculatesArea)
{
    const Triangle triangle{6.0, 3.0, [](Triangle const&) {}};

    EXPECT_THAT(triangle.base(), DoubleNear(6.0, tolerance));
    EXPECT_THAT(triangle.height(), DoubleNear(3.0, tolerance));
    EXPECT_THAT(triangle.calculate_area(), DoubleNear(9.0, tolerance));
}

TEST(FunctionStrategyTriangle, DrawDelegatesToCurrentCallable)
{
    std::vector<DrawCall> calls;
    const Triangle triangle{6.0, 3.0, [&calls](Triangle const& shape) {
                                calls.push_back({"triangle", shape.base(), shape.height()});
                            }};

    triangle.draw();

    ASSERT_EQ(calls.size(), 1);
    expect_draw_call(calls.front(), "triangle", 6.0, 3.0);
}

TEST(FunctionStrategy, CanReplaceCallableStrategy)
{
    std::vector<std::string> calls;
    Circle circle{2.0, [&calls](Circle const&) {
                      calls.push_back("first");
                  }};

    circle.set_strategy([&calls](Circle const&) {
        calls.push_back("second");
    });

    circle.draw();

    EXPECT_THAT(calls, ElementsAre("second"));
}

TEST(FunctionStrategy, RejectsEmptyCallableInConstructor)
{
    const auto construct_without_strategy = [] {
        [[maybe_unused]] const Circle circle{2.0, {}};
    };

    EXPECT_THAT(construct_without_strategy, Throws<std::invalid_argument>());
}

TEST(FunctionStrategy, RejectsEmptyCallableWhenReplacing)
{
    Circle circle{2.0, [](Circle const&) {}};

    const auto replace_with_empty_strategy = [&circle] {
        circle.set_strategy({});
    };

    EXPECT_THAT(replace_with_empty_strategy, Throws<std::invalid_argument>());
}

TEST(FunctionStrategyDrawStrategies, SendCircleToApiWritesCircleDetails)
{
    const Circle circle{2.5, [](Circle const&) {}};
    const CoutCapture capture;

    send_circle_to_api(circle);

    EXPECT_THAT(capture.str(), HasSubstr("Circle with radius 2.5 has been sent to the API"));
}

TEST(FunctionStrategyDrawStrategies, SendRectangleToApiWritesRectangleDetails)
{
    const Rectangle rectangle{4.0, 2.5, [](Rectangle const&) {}};
    const CoutCapture capture;

    send_rectangle_to_api(rectangle);

    EXPECT_THAT(capture.str(), HasSubstr("Rectangle with width 4 and height 2.5 has been sent to the API"));
}

TEST(FunctionStrategyDrawStrategies, SendTriangleToApiWritesTriangleDetails)
{
    const Triangle triangle{6.0, 3.0, [](Triangle const&) {}};
    const CoutCapture capture;

    send_triangle_to_api(triangle);

    EXPECT_THAT(capture.str(), HasSubstr("Triangle with base 6 and height 3 has been sent to the API"));
}

}  // namespace
