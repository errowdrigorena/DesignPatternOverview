#pragma once

#include <vector>

namespace bridge_pattern_common {

struct Point {
    double x{};
    double y{};
};

using ShapePath = std::vector<Point>;

}  // namespace bridge_pattern_common
