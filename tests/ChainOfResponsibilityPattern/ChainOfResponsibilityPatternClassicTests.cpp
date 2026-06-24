#include <ChainOfResponsibilityPattern_classic/AreaShapeHandler.hpp>
#include <ChainOfResponsibilityPattern_classic/DrawShapeHandler.hpp>
#include <ChainOfResponsibilityPattern_common/ShapeRequest.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <numbers>

namespace {

constexpr double tolerance = 1e-9;

using chain_of_responsibility_pattern_classic::AreaShapeHandler;
using chain_of_responsibility_pattern_classic::DrawShapeHandler;
using chain_of_responsibility_pattern_common::ShapeOperation;
using chain_of_responsibility_pattern_common::ShapeRequest;

TEST(ChainOfResponsibilityClassic, FirstHandlerProcessesMatchingDrawRequest)
{
    DrawShapeHandler handler;
    const auto rectangle = shapes_traditional::Rectangle::create(4.0, 2.0);
    ShapeRequest request{*rectangle, ShapeOperation::draw};

    testing::internal::CaptureStdout();
    EXPECT_TRUE(handler.handle(request));
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, testing::Eq("Drawing a rectangle with width 4 and height 2\n"));
    EXPECT_FALSE(request.area.has_value());
}

TEST(ChainOfResponsibilityClassic, PassesAreaRequestToSuccessor)
{
    DrawShapeHandler first_handler;
    first_handler.set_successor(std::make_unique<AreaShapeHandler>());

    const auto circle = shapes_traditional::Circle::create(3.0);
    ShapeRequest request{*circle, ShapeOperation::calculate_area};

    EXPECT_TRUE(first_handler.handle(request));
    ASSERT_TRUE(request.area.has_value());
    EXPECT_NEAR(*request.area, std::numbers::pi_v<double> * 9.0, tolerance);
}

TEST(ChainOfResponsibilityClassic, ReturnsFalseWhenNoHandlerAcceptsRequest)
{
    AreaShapeHandler handler;
    const auto circle = shapes_traditional::Circle::create(3.0);
    ShapeRequest request{*circle, ShapeOperation::draw};

    EXPECT_FALSE(handler.handle(request));
    EXPECT_FALSE(request.area.has_value());
}

TEST(ChainOfResponsibilityClassic, OneChainRoutesEachRequestTypeToTheCorrectHandlerWithoutCallerInvolvement)
{
    DrawShapeHandler draw_handler;
    draw_handler.set_successor(std::make_unique<AreaShapeHandler>());

    const auto circle = shapes_traditional::Circle::create(3.0);
    const auto rectangle = shapes_traditional::Rectangle::create(4.0, 2.0);

    ShapeRequest draw_request{*rectangle, ShapeOperation::draw};
    testing::internal::CaptureStdout();
    ASSERT_TRUE(draw_handler.handle(draw_request));
    const auto output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Drawing a rectangle with width 4 and height 2\n");

    ShapeRequest area_request{*circle, ShapeOperation::calculate_area};
    ASSERT_TRUE(draw_handler.handle(area_request));
    ASSERT_TRUE(area_request.area.has_value());
    EXPECT_NEAR(*area_request.area, std::numbers::pi_v<double> * 9.0, tolerance);
}

}  // namespace
