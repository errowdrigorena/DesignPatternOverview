#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <functional>
#include <memory>
#include <string_view>

namespace abstract_factory_pattern_modern {

using CircleCreator = std::function<std::unique_ptr<shapes_traditional::Shapes>(double)>;
using RectangleCreator = std::function<std::unique_ptr<shapes_traditional::Shapes>(double, double)>;
using TriangleCreator = std::function<std::unique_ptr<shapes_traditional::Shapes>(double, double)>;

struct ShapeFamilyFactory {
    std::string_view family;
    CircleCreator create_circle;
    RectangleCreator create_rectangle;
    TriangleCreator create_triangle;
};

[[nodiscard]] ShapeFamilyFactory make_wireframe_shape_factory();
[[nodiscard]] ShapeFamilyFactory make_solid_shape_factory();

}  // namespace abstract_factory_pattern_modern
