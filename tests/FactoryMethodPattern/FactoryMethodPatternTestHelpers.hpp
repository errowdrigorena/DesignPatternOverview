#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace factory_method_pattern_tests {

constexpr double tolerance = 1e-9;

template <typename Shape>
void expect_shape_with_area(const shapes_traditional::Shape& shape, const double expected_area)
{
    EXPECT_NE(dynamic_cast<const Shape*>(&shape), nullptr);
    EXPECT_THAT(shape.calculate_area(), testing::DoubleNear(expected_area, tolerance));
}

}  // namespace factory_method_pattern_tests
