#include <ChainOfResponsibilityPattern_common/ShapeRequest.hpp>
#include <ChainOfResponsibilityPattern_modern/ShapeRequestChain.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <stdexcept>

namespace {

constexpr double tolerance = 1e-9;

using chain_of_responsibility_pattern_common::ShapeOperation;
using chain_of_responsibility_pattern_common::ShapeRequest;
using chain_of_responsibility_pattern_modern::ShapeRequestChain;

TEST(ChainOfResponsibilityModern, StopsAtTheFirstHandlerThatAcceptsRequest)
{
    ShapeRequestChain chain;
    chain.add([](ShapeRequest& request) {
        if (request.operation != ShapeOperation::draw) {
            return false;
        }

        request.shape.draw();
        return true;
    });
    chain.add([](ShapeRequest&) {
        ADD_FAILURE() << "The next handler must not run after a request is handled";
        return true;
    });

    const auto rectangle = shapes_traditional::Rectangle::create(4.0, 2.0);
    ShapeRequest request{*rectangle, ShapeOperation::draw};

    testing::internal::CaptureStdout();
    EXPECT_TRUE(chain.handle(request));
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, testing::Eq("Drawing a rectangle with width 4 and height 2\n"));
}

TEST(ChainOfResponsibilityModern, PassesRequestToTheHandlerThatCanCalculateArea)
{
    ShapeRequestChain chain;
    chain.add([](ShapeRequest&) { return false; });
    chain.add([](ShapeRequest& request) {
        if (request.operation != ShapeOperation::calculate_area) {
            return false;
        }

        request.area = request.shape.calculate_area();
        return true;
    });

    const auto circle = shapes_traditional::Circle::create(3.0);
    ShapeRequest request{*circle, ShapeOperation::calculate_area};

    EXPECT_TRUE(chain.handle(request));
    ASSERT_TRUE(request.area.has_value());
    EXPECT_NEAR(*request.area, std::numbers::pi_v<double> * 9.0, tolerance);
}

TEST(ChainOfResponsibilityModern, ReturnsFalseWhenNoHandlerAcceptsRequest)
{
    ShapeRequestChain chain;
    chain.add([](ShapeRequest&) { return false; });

    const auto circle = shapes_traditional::Circle::create(3.0);
    ShapeRequest request{*circle, ShapeOperation::draw};

    EXPECT_FALSE(chain.handle(request));
}

TEST(ChainOfResponsibilityModern, RejectsEmptyHandlers)
{
    ShapeRequestChain chain;

    EXPECT_THROW(chain.add({}), std::invalid_argument);
}

}  // namespace
