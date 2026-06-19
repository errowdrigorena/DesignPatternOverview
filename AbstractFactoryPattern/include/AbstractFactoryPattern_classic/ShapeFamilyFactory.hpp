#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <memory>

namespace abstract_factory_pattern_classic {

class ShapeFamilyFactory {
public:
    virtual ~ShapeFamilyFactory() = default;

    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shapes> create_circle(
        double radius) const = 0;
    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shapes> create_rectangle(
        double width,
        double height) const = 0;
    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shapes> create_triangle(
        double base,
        double height) const = 0;
};

}  // namespace abstract_factory_pattern_classic
