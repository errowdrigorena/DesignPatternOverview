#include <IteratorPattern_modern/ranges/ShapeCollection.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <gtest/gtest.h>

#include <concepts>
#include <numbers>
#include <ranges>
#include <stdexcept>
#include <vector>

namespace {

constexpr double tolerance = 1e-9;

TEST(IteratorModernRanges, TraversesPolymorphicShapesAsARange)
{
    iterator_pattern_modern::ranges::ShapeCollection shapes;
    shapes.add(shapes_traditional::Circle::create(3.0));
    shapes.add(shapes_traditional::Rectangle::create(4.0, 2.0));
    shapes.add(shapes_traditional::Triangle::create(6.0, 3.0));

    const auto shape_range = shapes.shapes();
    static_assert(std::ranges::forward_range<decltype(shape_range)>);
    static_assert(std::same_as<decltype(shape_range.begin()), decltype(shape_range.end())>);

    std::vector<double> areas;
    for (const shapes_traditional::Shape& shape : shape_range) {
        areas.push_back(shape.calculate_area());
    }

    ASSERT_EQ(areas.size(), 3U);
    EXPECT_NEAR(areas[0], std::numbers::pi_v<double> * 9.0, tolerance);
    EXPECT_NEAR(areas[1], 8.0, tolerance);
    EXPECT_NEAR(areas[2], 9.0, tolerance);
}

TEST(IteratorModernRanges, SupportsAnEmptyRange)
{
    const iterator_pattern_modern::ranges::ShapeCollection shapes;
    const auto shape_range = shapes.shapes();

    EXPECT_EQ(shape_range.begin(), shape_range.end());
}

TEST(IteratorModernRanges, RejectsNullShapes)
{
    iterator_pattern_modern::ranges::ShapeCollection shapes;

    EXPECT_THROW(shapes.add(nullptr), std::invalid_argument);
}

}  // namespace
