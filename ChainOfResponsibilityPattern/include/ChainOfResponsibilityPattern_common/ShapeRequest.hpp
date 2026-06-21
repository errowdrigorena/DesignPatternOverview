#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <optional>

namespace chain_of_responsibility_pattern_common {

enum class ShapeOperation {
    draw,
    calculate_area
};

struct ShapeRequest {
    const shapes_traditional::Shapes& shape;
    ShapeOperation operation;
    std::optional<double> area;
};

}  // namespace chain_of_responsibility_pattern_common
