#include "FactoryMethodPatternTestHelpers.hpp"

#include <FactoryMethodPattern_modern/ConcreteCreator.hpp>
#include <FactoryMethodPattern_modern/DynamicFactory.hpp>
#include <FactoryMethodPattern_modern/ShapeRegistry.hpp>
#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Shape.hpp>
#include <Shapes_traditional/Triangle.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <stdexcept>
#include <string>

namespace {

using factory_method_pattern_tests::expect_shape_with_area;
using simple_factory_pseudo_pattern::ShapeType;
using testing::NotNull;
using testing::Throws;

TEST(FactoryMethodModern, DynamicRegistryCreatesKnownShape)
{
    const factory_method_pattern_modern::ShapeRegistry registry;

    const auto shape = registry.create(ShapeType::triangle);

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Triangle>(*shape, 6.0);
}

TEST(FactoryMethodModern, DynamicFactoryRejectsUnknownKey)
{
    factory_method_pattern_modern::DynamicFactory<shapes_traditional::Shape, std::string> factory;
    factory.register_creator("circle", [] -> std::unique_ptr<shapes_traditional::Shape> {
        return std::make_unique<shapes_traditional::Circle>(6.0);
    });

    const auto create_unknown = [&factory] {
        [[maybe_unused]] const auto shape = factory.create("hexagon");
    };

    EXPECT_THAT(create_unknown, Throws<std::out_of_range>());
}

TEST(FactoryMethodModern, ConcreteCreatorForwardsConstructorArguments)
{
    const factory_method_pattern_modern::ConcreteCreator<
        shapes_traditional::Shape,
        shapes_traditional::Rectangle,
        double,
        double>
        creator;

    const auto shape = creator.create(5.0, 2.0);

    ASSERT_THAT(shape, NotNull());
    expect_shape_with_area<shapes_traditional::Rectangle>(*shape, 10.0);
}

TEST(FactoryMethodModern, DynamicFactoryCreatesAllRegisteredCreators)
{
    factory_method_pattern_modern::DynamicFactory<shapes_traditional::Shape, std::string> factory;
    factory.register_creator("circle", [] -> std::unique_ptr<shapes_traditional::Shape> {
        return std::make_unique<shapes_traditional::Circle>(6.0);
    });
    factory.register_creator("rectangle", [] -> std::unique_ptr<shapes_traditional::Shape> {
        return std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0);
    });
    factory.register_creator("triangle", [] -> std::unique_ptr<shapes_traditional::Shape> {
        return std::make_unique<shapes_traditional::Triangle>(4.0, 3.0);
    });

    EXPECT_NEAR(factory.create("circle")->calculate_area(), std::numbers::pi_v<double> * 36.0, 1e-9);
    EXPECT_DOUBLE_EQ(factory.create("rectangle")->calculate_area(), 12.0);
    EXPECT_DOUBLE_EQ(factory.create("triangle")->calculate_area(), 6.0);
}

}  // namespace
