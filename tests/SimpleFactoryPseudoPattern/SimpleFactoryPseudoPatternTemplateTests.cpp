#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>
#include <SimpleFactoryPseudoPattern_template/ShapeFactory.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>

namespace {

using testing::DoubleNear;
using testing::NotNull;

constexpr double tolerance = 1e-9;

template <typename Shape>
void expect_shape_with_area(const shapes_traditional::Shapes& shape, const double expected_area)
{
    EXPECT_NE(dynamic_cast<const Shape*>(&shape), nullptr);
    EXPECT_THAT(shape.calculate_area(), DoubleNear(expected_area, tolerance));
}

TEST(SimpleFactoryTemplate, CircleTagCreatesCircle)
{
    using simple_factory_pseudo_pattern_template::CircleTag;
    using simple_factory_pseudo_pattern_template::ShapeFactory;

    const auto shape = ShapeFactory<CircleTag>::create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Circle>(*shape, std::numbers::pi_v<double> * 36.0);
}

TEST(SimpleFactoryTemplate, RectangleTagCreatesRectangle)
{
    using simple_factory_pseudo_pattern_template::RectangleTag;
    using simple_factory_pseudo_pattern_template::ShapeFactory;

    const auto shape = ShapeFactory<RectangleTag>::create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Rectangle>(*shape, 12.0);
}

TEST(SimpleFactoryTemplate, TriangleTagCreatesTriangle)
{
    using simple_factory_pseudo_pattern_template::ShapeFactory;
    using simple_factory_pseudo_pattern_template::TriangleTag;

    const auto shape = ShapeFactory<TriangleTag>::create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Triangle>(*shape, 6.0);
}

}  // namespace
