#include <IteratorPattern_modern/iterators/ShapeCollection.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <gtest/gtest.h>

#include <concepts>
#include <numbers>
#include <stdexcept>
#include <vector>

namespace {

constexpr double tolerance = 1e-9;

TEST(IteratorModernIterators, TraversesPolymorphicShapesWithAStandardIteratorPair)
{
    iterator_pattern_modern::iterators::ShapeCollection shapes;
    shapes.add(shapes_traditional::Circle::create(3.0));
    shapes.add(shapes_traditional::Rectangle::create(4.0, 2.0));
    shapes.add(shapes_traditional::Triangle::create(6.0, 3.0));

    std::vector<double> areas;
    const auto [begin, end] = shapes.iterators();
    for (auto iterator = begin; iterator != end; ++iterator) {
        areas.push_back((*iterator)->calculate_area());
    }

    ASSERT_EQ(areas.size(), 3U);
    EXPECT_NEAR(areas[0], std::numbers::pi_v<double> * 9.0, tolerance);
    EXPECT_NEAR(areas[1], 8.0, tolerance);
    EXPECT_NEAR(areas[2], 9.0, tolerance);
}

TEST(IteratorModernIterators, ExposesMutableAndConstStandardIterators)
{
    using ShapeCollection = iterator_pattern_modern::iterators::ShapeCollection;

    ShapeCollection shapes;
    const ShapeCollection& const_shapes = shapes;

    static_assert(std::same_as<decltype(shapes.iterators()), std::pair<ShapeCollection::iterator, ShapeCollection::iterator>>);
    static_assert(std::same_as<decltype(const_shapes.iterators()), std::pair<ShapeCollection::const_iterator, ShapeCollection::const_iterator>>);

    const auto [begin, end] = shapes.iterators();
    EXPECT_EQ(begin, end);
}

TEST(IteratorModernIterators, RejectsNullShapes)
{
    iterator_pattern_modern::iterators::ShapeCollection shapes;

    EXPECT_THROW(shapes.add(nullptr), std::invalid_argument);
}

}  // namespace
