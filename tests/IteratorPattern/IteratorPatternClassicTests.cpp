#include <IteratorPattern_classic/ShapeCollection.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <gtest/gtest.h>

#include <numbers>
#include <stdexcept>
#include <vector>

namespace {

constexpr double tolerance = 1e-9;

TEST(IteratorClassic, TraversesPolymorphicShapesInInsertionOrder)
{
    iterator_pattern_classic::ShapeCollection shapes;
    shapes.add(shapes_traditional::Circle::create(3.0));
    shapes.add(shapes_traditional::Rectangle::create(4.0, 2.0));
    shapes.add(shapes_traditional::Triangle::create(6.0, 3.0));

    const auto iterator = shapes.create_iterator();
    std::vector<double> areas;

    for (iterator->first(); !iterator->is_done(); iterator->next()) {
        areas.push_back(iterator->current_item().calculate_area());
    }

    ASSERT_EQ(areas.size(), 3U);
    EXPECT_NEAR(areas[0], std::numbers::pi_v<double> * 9.0, tolerance);
    EXPECT_NEAR(areas[1], 8.0, tolerance);
    EXPECT_NEAR(areas[2], 9.0, tolerance);
}

TEST(IteratorClassic, EmptyCollectionStartsDone)
{
    const iterator_pattern_classic::ShapeCollection shapes;
    const auto iterator = shapes.create_iterator();

    iterator->first();

    EXPECT_TRUE(iterator->is_done());
    EXPECT_THROW(static_cast<void>(iterator->current_item()), std::out_of_range);
}

TEST(IteratorClassic, RejectsNullShapes)
{
    iterator_pattern_classic::ShapeCollection shapes;

    EXPECT_THROW(shapes.add(nullptr), std::invalid_argument);
}

}  // namespace
