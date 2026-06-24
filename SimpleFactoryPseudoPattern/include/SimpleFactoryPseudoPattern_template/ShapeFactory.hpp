#pragma once

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Shape.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <memory>

namespace simple_factory_pseudo_pattern_template {

struct CircleTag {};
struct RectangleTag {};
struct TriangleTag {};

template <typename ShapeTag>
class ShapeFactory;

template <>
class ShapeFactory<CircleTag> {
public:
    [[nodiscard]] static std::unique_ptr<shapes_traditional::Shape> create()
    {
        return std::make_unique<shapes_traditional::Circle>(6.0);
    }
};

template <>
class ShapeFactory<RectangleTag> {
public:
    [[nodiscard]] static std::unique_ptr<shapes_traditional::Shape> create()
    {
        return std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0);
    }
};

template <>
class ShapeFactory<TriangleTag> {
public:
    [[nodiscard]] static std::unique_ptr<shapes_traditional::Shape> create()
    {
        return std::make_unique<shapes_traditional::Triangle>(4.0, 3.0);
    }
};

}  // namespace simple_factory_pseudo_pattern_template
