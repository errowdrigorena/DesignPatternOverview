#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>
#include <SimpleFactoryPseudoPattern_map/ShapeFactory.hpp>
#include <SimpleFactoryPseudoPattern_static/CircleFactory.hpp>
#include <SimpleFactoryPseudoPattern_static/RectangleFactory.hpp>
#include <SimpleFactoryPseudoPattern_static/TriangleFactory.hpp>
#include <SimpleFactoryPseudoPattern_switch/ShapeFactory.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <stdexcept>

namespace {

using simple_factory_pseudo_pattern::ShapeType;
using testing::DoubleNear;
using testing::NotNull;
using testing::Throws;

constexpr double tolerance = 1e-9;

template <typename Shape>
void expect_shape_with_area(const shapes_traditional::Shape& shape, const double expected_area)
{
    EXPECT_NE(dynamic_cast<const Shape*>(&shape), nullptr);
    EXPECT_THAT(shape.calculate_area(), DoubleNear(expected_area, tolerance));
}

TEST(SimpleFactorySwitch, CreatesCircle)
{
    const simple_factory_pseudo_pattern_switch::ShapeFactory factory;

    const auto shape = factory.create(ShapeType::circle);

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Circle>(*shape, std::numbers::pi_v<double> * 36.0);
}

TEST(SimpleFactorySwitch, CreatesRectangle)
{
    const simple_factory_pseudo_pattern_switch::ShapeFactory factory;

    const auto shape = factory.create(ShapeType::rectangle);

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Rectangle>(*shape, 12.0);
}

TEST(SimpleFactorySwitch, CreatesTriangle)
{
    const simple_factory_pseudo_pattern_switch::ShapeFactory factory;

    const auto shape = factory.create(ShapeType::triangle);

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Triangle>(*shape, 6.0);
}

TEST(SimpleFactorySwitch, RejectsUnknownShapeType)
{
    const simple_factory_pseudo_pattern_switch::ShapeFactory factory;

    const auto create_unknown_shape = [&factory] {
        [[maybe_unused]] const auto shape = factory.create(static_cast<ShapeType>(999));
    };

    EXPECT_THAT(create_unknown_shape, Throws<std::invalid_argument>());
}

TEST(SimpleFactoryMap, CreatesCircleByName)
{
    const simple_factory_pseudo_pattern_map::ShapeFactory factory;

    const auto shape = factory.create("circle");

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Circle>(*shape, std::numbers::pi_v<double> * 36.0);
}

TEST(SimpleFactoryMap, CreatesRectangleByName)
{
    const simple_factory_pseudo_pattern_map::ShapeFactory factory;

    const auto shape = factory.create("rectangle");

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Rectangle>(*shape, 12.0);
}

TEST(SimpleFactoryMap, CreatesTriangleByName)
{
    const simple_factory_pseudo_pattern_map::ShapeFactory factory;

    const auto shape = factory.create("triangle");

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Triangle>(*shape, 6.0);
}

TEST(SimpleFactoryMap, RejectsUnknownShapeName)
{
    const simple_factory_pseudo_pattern_map::ShapeFactory factory;

    const auto create_unknown_shape = [&factory] {
        [[maybe_unused]] const auto shape = factory.create("hexagon");
    };

    EXPECT_THAT(create_unknown_shape, Throws<std::invalid_argument>());
}

TEST(SimpleFactoryStatic, CircleFactoryCreatesCircle)
{
    const simple_factory_pseudo_pattern_static::CircleFactory factory;

    const auto shape = factory.create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Circle>(*shape, std::numbers::pi_v<double> * 36.0);
}

TEST(SimpleFactoryStatic, RectangleFactoryCreatesRectangle)
{
    const simple_factory_pseudo_pattern_static::RectangleFactory factory;

    const auto shape = factory.create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Rectangle>(*shape, 12.0);
}

TEST(SimpleFactoryStatic, TriangleFactoryCreatesTriangle)
{
    const simple_factory_pseudo_pattern_static::TriangleFactory factory;

    const auto shape = factory.create();

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Triangle>(*shape, 6.0);
}

}  // namespace
