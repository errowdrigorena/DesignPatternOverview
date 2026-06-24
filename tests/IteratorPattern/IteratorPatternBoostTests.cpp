#include <IteratorPattern_boost/ShapeCollection.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <gtest/gtest.h>

#include <iterator>
#include <numbers>
#include <stdexcept>
#include <vector>

namespace {

constexpr double tolerance = 1e-9;

TEST(BoostIteratorFacade, TraversesCollectionWithRangeForLoop)
{
    iterator_pattern_boost::ShapeCollection shapes;
    shapes.add(shapes_traditional::Circle::create(3.0));
    shapes.add(shapes_traditional::Rectangle::create(4.0, 2.0));
    shapes.add(shapes_traditional::Triangle::create(6.0, 3.0));

    std::vector<double> areas;
    for (const shapes_traditional::Shape& shape : shapes) {
        areas.push_back(shape.calculate_area());
    }

    ASSERT_EQ(areas.size(), 3U);
    EXPECT_NEAR(areas[0], std::numbers::pi_v<double> * 9.0, tolerance);
    EXPECT_NEAR(areas[1], 8.0, tolerance);
    EXPECT_NEAR(areas[2], 9.0, tolerance);
}

TEST(BoostIteratorFacade, EmptyCollectionHasEqualBeginAndEnd)
{
    iterator_pattern_boost::ShapeCollection shapes;
    EXPECT_EQ(shapes.begin(), shapes.end());
}

TEST(BoostIteratorFacade, IteratorSatisfiesBidirectionalCategory)
{
    using Iter = iterator_pattern_boost::ShapeIterator;
    static_assert(std::bidirectional_iterator<Iter>);
}

TEST(BoostIteratorFacade, DecrementReversesIncrement)
{
    iterator_pattern_boost::ShapeCollection shapes;
    shapes.add(shapes_traditional::Circle::create(1.0));
    shapes.add(shapes_traditional::Rectangle::create(2.0, 3.0));

    auto it = shapes.begin();
    ++it;
    --it;

    EXPECT_EQ(&*it, &*shapes.begin());
}

TEST(BoostIteratorFacade, RejectsNullShapes)
{
    iterator_pattern_boost::ShapeCollection shapes;
    EXPECT_THROW(shapes.add(nullptr), std::invalid_argument);
}

}  // namespace
