#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <memory>

namespace abstract_factory_pattern_classic {

class ShapeFamilyFactory {
public:
    virtual ~ShapeFamilyFactory() = default;

    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shape> create_circle(
        double radius) const = 0;
    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shape> create_rectangle(
        double width,
        double height) const = 0;
    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shape> create_triangle(
        double base,
        double height) const = 0;
};

}  // namespace abstract_factory_pattern_classic
