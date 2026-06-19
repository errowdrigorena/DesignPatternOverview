#include "FactoryMethodPatternTestHelpers.hpp"

#include <FactoryMethodPattern_simple_factory/ShapeScene.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

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

}  // namespace
