#include <AbstractFactoryPattern_common/ShapeFamilies.hpp>
#include <AbstractFactoryPattern_modern/ShapeFamilyFactory.hpp>
#include <AbstractFactoryPattern_modern/ShapeScene.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>

namespace {

constexpr double tolerance = 1e-9;

TEST(AbstractFactoryModern, CreatesAWireframeShapeFamilyFactory)
{
    const auto factory = abstract_factory_pattern_modern::make_wireframe_shape_factory();

    const auto circle = factory.create_circle(6.0);
    const auto rectangle = factory.create_rectangle(4.0, 3.0);
    const auto triangle = factory.create_triangle(4.0, 3.0);

    EXPECT_EQ(factory.family, "wireframe");
    EXPECT_NE(dynamic_cast<const abstract_factory_pattern_common::WireframeCircle*>(circle.get()), nullptr);
    EXPECT_NE(dynamic_cast<const abstract_factory_pattern_common::WireframeRectangle*>(rectangle.get()), nullptr);
    EXPECT_NE(dynamic_cast<const abstract_factory_pattern_common::WireframeTriangle*>(triangle.get()), nullptr);
}

TEST(AbstractFactoryModern, CreatesASolidShapeFamilyFactory)
{
    const auto factory = abstract_factory_pattern_modern::make_solid_shape_factory();

    const auto circle = factory.create_circle(6.0);
    const auto rectangle = factory.create_rectangle(4.0, 3.0);
    const auto triangle = factory.create_triangle(4.0, 3.0);

    EXPECT_EQ(factory.family, "solid");
    EXPECT_NE(dynamic_cast<const abstract_factory_pattern_common::SolidCircle*>(circle.get()), nullptr);
    EXPECT_NE(dynamic_cast<const abstract_factory_pattern_common::SolidRectangle*>(rectangle.get()), nullptr);
    EXPECT_NE(dynamic_cast<const abstract_factory_pattern_common::SolidTriangle*>(triangle.get()), nullptr);
}

TEST(AbstractFactoryModern, SceneUsesTheInjectedFactoryForTheWholeShapeFamily)
{
    const abstract_factory_pattern_modern::ShapeScene scene{
        abstract_factory_pattern_modern::make_solid_shape_factory()};

    const auto shapes = scene.create_sample_scene();

    ASSERT_EQ(shapes.size(), 3U);
    for (const auto& shape : shapes) {
        const auto* styled_shape = dynamic_cast<const abstract_factory_pattern_common::StyledShape*>(shape.get());
        ASSERT_THAT(styled_shape, testing::NotNull());
        EXPECT_EQ(styled_shape->family(), "solid");
    }
}

TEST(AbstractFactoryModern, ScenePreservesGeometryWhenSwitchingFactories)
{
    const abstract_factory_pattern_modern::ShapeScene wireframe_scene{
        abstract_factory_pattern_modern::make_wireframe_shape_factory()};
    const abstract_factory_pattern_modern::ShapeScene solid_scene{
        abstract_factory_pattern_modern::make_solid_shape_factory()};
    const auto expected_area = std::numbers::pi_v<double> * 36.0 + 12.0 + 6.0;

    EXPECT_THAT(wireframe_scene.sample_scene_area(), testing::DoubleNear(expected_area, tolerance));
    EXPECT_THAT(solid_scene.sample_scene_area(), testing::DoubleNear(expected_area, tolerance));
}

TEST(AbstractFactoryModern, FactoriesUseCreationArguments)
{
    const abstract_factory_pattern_modern::ShapeScene scene{
        abstract_factory_pattern_modern::make_wireframe_shape_factory()};

    const auto expected_area = std::numbers::pi_v<double> * 9.0 + 14.0 + 20.0;

    EXPECT_THAT(
        scene.sample_scene_area(3.0, 7.0, 2.0, 10.0, 4.0),
        testing::DoubleNear(expected_area, tolerance));
}

}  // namespace
