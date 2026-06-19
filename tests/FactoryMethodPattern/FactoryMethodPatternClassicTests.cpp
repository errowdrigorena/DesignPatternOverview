#include "FactoryMethodPatternTestHelpers.hpp"

#include <FactoryMethodPattern_classic/CircleCreator.hpp>
#include <FactoryMethodPattern_classic/RectangleCreator.hpp>
#include <FactoryMethodPattern_classic/TriangleCreator.hpp>
#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>

namespace {

using factory_method_pattern_tests::expect_shape_with_area;
using factory_method_pattern_tests::tolerance;
using testing::DoubleNear;
using testing::NotNull;

TEST(FactoryMethodClassic, CircleCreatorCreatesCircle)
{
    const factory_method_pattern_classic::CircleCreator creator;

    const auto shape = creator.create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Circle>(*shape, std::numbers::pi_v<double> * 36.0);
}

TEST(FactoryMethodClassic, RectangleCreatorCreatesRectangle)
{
    const factory_method_pattern_classic::RectangleCreator creator;

    const auto shape = creator.create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Rectangle>(*shape, 12.0);
}

TEST(FactoryMethodClassic, TriangleCreatorCreatesTriangle)
{
    const factory_method_pattern_classic::TriangleCreator creator;

    const auto shape = creator.create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Triangle>(*shape, 6.0);
}

TEST(FactoryMethodClassic, CreatorOperationUsesTheFactoryMethod)
{
    const factory_method_pattern_classic::RectangleCreator creator;

    EXPECT_THAT(creator.preview_area(), DoubleNear(12.0, tolerance));
}

}  // namespace
