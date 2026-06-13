#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <string_view>

namespace test_doubles::spies {

struct DrawCall {
    std::string shape;
    double first_dimension;
    std::optional<double> second_dimension;
};

inline void expect_draw_call(
    const DrawCall& call,
    std::string_view expected_shape,
    const double expected_first_dimension,
    const std::optional<double> expected_second_dimension)
{
    constexpr double tolerance = 1e-9;

    EXPECT_EQ(call.shape, expected_shape);
    EXPECT_THAT(call.first_dimension, testing::DoubleNear(expected_first_dimension, tolerance));
    EXPECT_EQ(call.second_dimension.has_value(), expected_second_dimension.has_value());

    if (expected_second_dimension) {
        EXPECT_THAT(*call.second_dimension, testing::DoubleNear(*expected_second_dimension, tolerance));
    }
}

}  // namespace test_doubles::spies
