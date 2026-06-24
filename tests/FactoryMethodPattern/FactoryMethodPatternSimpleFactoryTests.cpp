#include "FactoryMethodPatternTestHelpers.hpp"

#include <FactoryMethodPattern_simple_factory/ShapeScene.hpp>
#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>

namespace {

using factory_method_pattern_tests::expect_shape_with_area;
using simple_factory_pseudo_pattern::ShapeType;
using testing::NotNull;

TEST(FactoryMethodSimpleFactory, SceneUsesSwitchFactory)
{
    const factory_method_pattern_simple_factory::ShapeScene scene;

    const auto shape = scene.add_shape(ShapeType::rectangle);

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Rectangle>(*shape, 12.0);
}

TEST(FactoryMethodSimpleFactory, SceneCreatesAnyShapeTypeWithCorrectGeometry)
{
    const factory_method_pattern_simple_factory::ShapeScene scene;

    const auto circle = scene.add_shape(ShapeType::circle);
    const auto rectangle = scene.add_shape(ShapeType::rectangle);
    const auto triangle = scene.add_shape(ShapeType::triangle);

    ASSERT_THAT(circle, NotNull());
    ASSERT_THAT(rectangle, NotNull());
    ASSERT_THAT(triangle, NotNull());
    expect_shape_with_area<shapes_traditional::Circle>(*circle, std::numbers::pi_v<double> * 36.0);
    expect_shape_with_area<shapes_traditional::Rectangle>(*rectangle, 12.0);
    expect_shape_with_area<shapes_traditional::Triangle>(*triangle, 6.0);
}

}  // namespace
