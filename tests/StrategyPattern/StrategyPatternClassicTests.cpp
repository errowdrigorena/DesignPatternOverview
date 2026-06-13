#include <Shapes_strategy_classic/Circle_strategy.hpp>
#include <Shapes_strategy_classic/Rectangle_strategy.hpp>
#include <Shapes_strategy_classic/Triangle_strategy.hpp>
#include <TestDoubles/Spies/RecordingDrawStrategy.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <stdexcept>
#include <vector>

namespace {

using shapes_strategy::Circle_strategy;
using shapes_strategy::Rectangle_strategy;
using shapes_strategy::Triangle_strategy;
using test_doubles::spies::DrawCall;
using test_doubles::spies::expect_draw_call;
using test_doubles::spies::make_recording_strategy;
using testing::DoubleNear;
using testing::Throws;

constexpr double tolerance = 1e-9;

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

}  // namespace
