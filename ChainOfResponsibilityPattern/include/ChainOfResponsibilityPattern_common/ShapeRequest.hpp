#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <optional>

namespace chain_of_responsibility_pattern_common {

enum class ShapeOperation {
    draw,
    calculate_area
};

struct ShapeRequest {
    const shapes_traditional::Shape& shape;
    ShapeOperation operation;
    std::optional<double> area;
};

}  // namespace chain_of_responsibility_pattern_common
