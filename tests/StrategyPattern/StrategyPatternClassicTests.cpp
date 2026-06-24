#include <Shapes_strategy_classic/ApiDrawStrategy.hpp>
#include <Shapes_strategy_classic/Circle_strategy.hpp>
#include <Shapes_strategy_classic/Rectangle_strategy.hpp>
#include <Shapes_strategy_classic/StarDrawStrategy.hpp>
#include <Shapes_strategy_classic/Triangle_strategy.hpp>
#include <TestDoubles/Spies/RecordingDrawStrategy.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <numbers>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

using shapes_strategy::Circle_strategy;
using shapes_strategy::ApiDrawStrategy;
using shapes_strategy::Rectangle_strategy;
using shapes_strategy::StarDrawStrategy;
using shapes_strategy::Triangle_strategy;
using test_doubles::spies::DrawCall;
using test_doubles::spies::expect_draw_call;
using test_doubles::spies::make_recording_strategy;
using testing::DoubleNear;
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

TEST(ClassicStrategyCircle, CalculatesArea)
{
    std::vector<DrawCall> calls;
    const Circle_strategy circle{3.0, make_recording_strategy(calls)};

    EXPECT_THAT(circle.calculate_area(), DoubleNear(std::numbers::pi_v<double> * 9.0, tolerance));
}

TEST(ClassicStrategyCircle, DrawDelegatesToCurrentStrategy)
{
    std::vector<DrawCall> calls;
    const Circle_strategy circle{2.5, make_recording_strategy(calls)};

    circle.draw();

    ASSERT_EQ(calls.size(), 1);
    expect_draw_call(calls.front(), "circle", 2.5, std::nullopt);
}

TEST(ClassicStrategyRectangle, CalculatesArea)
{
    std::vector<DrawCall> calls;
    const Rectangle_strategy rectangle{4.0, 2.5, make_recording_strategy(calls)};

    EXPECT_THAT(rectangle.calculate_area(), DoubleNear(10.0, tolerance));
}

TEST(ClassicStrategyRectangle, DrawDelegatesToCurrentStrategy)
{
    std::vector<DrawCall> calls;
    const Rectangle_strategy rectangle{4.0, 2.5, make_recording_strategy(calls)};

    rectangle.draw();

    ASSERT_EQ(calls.size(), 1);
    expect_draw_call(calls.front(), "rectangle", 4.0, 2.5);
}

TEST(ClassicStrategyTriangle, CalculatesArea)
{
    std::vector<DrawCall> calls;
    const Triangle_strategy triangle{6.0, 3.0, make_recording_strategy(calls)};

    EXPECT_THAT(triangle.calculate_area(), DoubleNear(9.0, tolerance));
}

TEST(ClassicStrategyTriangle, DrawDelegatesToCurrentStrategy)
{
    std::vector<DrawCall> calls;
    const Triangle_strategy triangle{6.0, 3.0, make_recording_strategy(calls)};

    triangle.draw();

    ASSERT_EQ(calls.size(), 1);
    expect_draw_call(calls.front(), "triangle", 6.0, 3.0);
}

TEST(ClassicStrategy, CanReplaceDrawStrategy)
{
    std::vector<DrawCall> calls;
    Circle_strategy circle{2.0, make_recording_strategy(calls)};

    circle.set_strategy(make_recording_strategy(calls));

    circle.draw();

    ASSERT_EQ(calls.size(), 1);
    expect_draw_call(calls.front(), "circle", 2.0, std::nullopt);
}

TEST(ClassicStrategy, RejectsNullStrategyInConstructor)
{
    const auto construct_without_strategy = [] {
        [[maybe_unused]] const Circle_strategy circle{2.0, nullptr};
    };

    EXPECT_THAT(construct_without_strategy, Throws<std::invalid_argument>());
}

TEST(ClassicStrategy, RejectsNullStrategyWhenReplacing)
{
    std::vector<DrawCall> calls;
    Circle_strategy circle{2.0, make_recording_strategy(calls)};

    const auto replace_with_null_strategy = [&circle] {
        circle.set_strategy(nullptr);
    };

    EXPECT_THAT(replace_with_null_strategy, Throws<std::invalid_argument>());
}

TEST(ClassicApiDrawStrategy, WritesShapeDetails)
{
    const ApiDrawStrategy strategy;
    const CoutCapture capture;

    strategy.draw_circle(2.5);
    strategy.draw_rectangle(4.0, 2.5);
    strategy.draw_triangle(6.0, 3.0);

    EXPECT_EQ(
        capture.str(),
        "Circle with radius 2.5 has been sent to the API\n"
        "Rectangle with width 4 and height 2.5 has been sent to the API\n"
        "Triangle with base 6 and height 3 has been sent to the API\n");
}

TEST(ClassicStarDrawStrategy, DrawsCircleWithStars)
{
    const StarDrawStrategy strategy;
    const CoutCapture capture;

    strategy.draw_circle(1.4);

    EXPECT_THAT(capture.str(), HasSubstr("Circle with radius 1.4\n"));
    EXPECT_THAT(capture.str(), HasSubstr("***"));
}

TEST(ClassicStarDrawStrategy, DrawsRectangleWithStars)
{
    const StarDrawStrategy strategy;
    const CoutCapture capture;

    strategy.draw_rectangle(3.0, 2.0);

    EXPECT_EQ(
        capture.str(),
        "Rectangle with width 3 and height 2\n"
        "***\n"
        "***\n");
}

TEST(ClassicStarDrawStrategy, DrawsTriangleWithStars)
{
    const StarDrawStrategy strategy;
    const CoutCapture capture;

    strategy.draw_triangle(4.0, 3.0);

    EXPECT_EQ(
        capture.str(),
        "Triangle with base 4 and height 3\n"
        "*\n"
        "**\n"
        "***\n");
}

TEST(ClassicStrategy, AnyShapeWorksWithAnyDrawStrategy)
{
    std::vector<DrawCall> calls;
    const Circle_strategy circle{2.5, make_recording_strategy(calls)};
    const Rectangle_strategy rectangle{4.0, 2.5, make_recording_strategy(calls)};
    const Triangle_strategy triangle{6.0, 3.0, make_recording_strategy(calls)};

    circle.draw();
    rectangle.draw();
    triangle.draw();

    ASSERT_EQ(calls.size(), 3U);
    expect_draw_call(calls[0], "circle", 2.5, std::nullopt);
    expect_draw_call(calls[1], "rectangle", 4.0, 2.5);
    expect_draw_call(calls[2], "triangle", 6.0, 3.0);
}

TEST(ClassicStrategy, ReplacingStrategyChangesDrawBehaviourWithoutChangingTheShape)
{
    std::vector<DrawCall> original_calls;
    std::vector<DrawCall> replacement_calls;
    Circle_strategy circle{2.0, make_recording_strategy(original_calls)};

    circle.set_strategy(make_recording_strategy(replacement_calls));
    circle.draw();

    EXPECT_TRUE(original_calls.empty());
    ASSERT_EQ(replacement_calls.size(), 1U);
    expect_draw_call(replacement_calls.front(), "circle", 2.0, std::nullopt);
}

}  // namespace
