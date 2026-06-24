#include <AbstractFactoryPattern_classic/SolidShapeFactory.hpp>
#include <AbstractFactoryPattern_classic/WireframeShapeFactory.hpp>
#include <AbstractFactoryPattern_classic/ShapeScene.hpp>
#include <AbstractFactoryPattern_common/ShapeFamilies.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>

namespace {

constexpr double tolerance = 1e-9;

template <typename Shape>
void expect_shape_family(const shapes_traditional::Shape& shape, const std::string_view family)
{
    const auto* styled_shape = dynamic_cast<const abstract_factory_pattern_common::StyledShape*>(&shape);
    ASSERT_THAT(styled_shape, testing::NotNull());
    EXPECT_EQ(styled_shape->family(), family);
    EXPECT_NE(dynamic_cast<const Shape*>(&shape), nullptr);
}

TEST(AbstractFactoryClassic, WireframeFactoryCreatesAWireframeShapeFamily)
{
    const abstract_factory_pattern_classic::WireframeShapeFactory factory;

    const auto circle = factory.create_circle(6.0);
    const auto rectangle = factory.create_rectangle(4.0, 3.0);
    const auto triangle = factory.create_triangle(4.0, 3.0);

    expect_shape_family<abstract_factory_pattern_common::WireframeCircle>(*circle, "wireframe");
    expect_shape_family<abstract_factory_pattern_common::WireframeRectangle>(*rectangle, "wireframe");
    expect_shape_family<abstract_factory_pattern_common::WireframeTriangle>(*triangle, "wireframe");
}

TEST(AbstractFactoryClassic, SolidFactoryCreatesASolidShapeFamily)
{
    const abstract_factory_pattern_classic::SolidShapeFactory factory;

    const auto circle = factory.create_circle(6.0);
    const auto rectangle = factory.create_rectangle(4.0, 3.0);
    const auto triangle = factory.create_triangle(4.0, 3.0);

    expect_shape_family<abstract_factory_pattern_common::SolidCircle>(*circle, "solid");
    expect_shape_family<abstract_factory_pattern_common::SolidRectangle>(*rectangle, "solid");
    expect_shape_family<abstract_factory_pattern_common::SolidTriangle>(*triangle, "solid");
}

TEST(AbstractFactoryClassic, SceneUsesOneFactoryForTheWholeShapeFamily)
{
    const abstract_factory_pattern_classic::WireframeShapeFactory factory;
    const abstract_factory_pattern_classic::ShapeScene scene{factory};

    const auto shapes = scene.create_sample_scene();

    ASSERT_EQ(shapes.size(), 3U);
    for (const auto& shape : shapes) {
        const auto* styled_shape = dynamic_cast<const abstract_factory_pattern_common::StyledShape*>(shape.get());
        ASSERT_THAT(styled_shape, testing::NotNull());
        EXPECT_EQ(styled_shape->family(), "wireframe");
    }
}

TEST(AbstractFactoryClassic, SceneKeepsTheSameGeometryAcrossFamilies)
{
    const abstract_factory_pattern_classic::WireframeShapeFactory wireframe_factory;
    const abstract_factory_pattern_classic::SolidShapeFactory solid_factory;
    const abstract_factory_pattern_classic::ShapeScene wireframe_scene{wireframe_factory};
    const abstract_factory_pattern_classic::ShapeScene solid_scene{solid_factory};

    const auto expected_area = std::numbers::pi_v<double> * 36.0 + 12.0 + 6.0;

    EXPECT_THAT(wireframe_scene.sample_scene_area(), testing::DoubleNear(expected_area, tolerance));
    EXPECT_THAT(solid_scene.sample_scene_area(), testing::DoubleNear(expected_area, tolerance));
}

TEST(AbstractFactoryClassic, FactoriesUseCreationArguments)
{
    const abstract_factory_pattern_classic::SolidShapeFactory factory;
    const abstract_factory_pattern_classic::ShapeScene scene{factory};

    const auto expected_area = std::numbers::pi_v<double> * 4.0 + 20.0 + 12.0;

    EXPECT_THAT(
        scene.sample_scene_area(2.0, 5.0, 4.0, 8.0, 3.0),
        testing::DoubleNear(expected_area, tolerance));
}

}  // namespace
