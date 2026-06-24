#pragma once

#include <AbstractFactoryPattern_classic/ShapeFamilyFactory.hpp>

namespace abstract_factory_pattern_classic {

class WireframeShapeFactory final : public ShapeFamilyFactory {
public:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shape> create_circle(
        double radius) const override;
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shape> create_rectangle(
        double width,
        double height) const override;
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shape> create_triangle(
        double base,
        double height) const override;
};

}  // namespace abstract_factory_pattern_classic
