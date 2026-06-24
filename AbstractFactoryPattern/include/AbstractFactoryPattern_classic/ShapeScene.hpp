#pragma once

#include <AbstractFactoryPattern_classic/ShapeFamilyFactory.hpp>

#include <memory>
#include <vector>

namespace abstract_factory_pattern_classic {

using ShapeCollection = std::vector<std::unique_ptr<shapes_traditional::Shape>>;

class ShapeScene {
public:
    explicit ShapeScene(const ShapeFamilyFactory& factory);

    [[nodiscard]] ShapeCollection create_sample_scene(
        double circle_radius = 6.0,
        double rectangle_width = 4.0,
        double rectangle_height = 3.0,
        double triangle_base = 4.0,
        double triangle_height = 3.0) const;
    [[nodiscard]] double sample_scene_area(
        double circle_radius = 6.0,
        double rectangle_width = 4.0,
        double rectangle_height = 3.0,
        double triangle_base = 4.0,
        double triangle_height = 3.0) const;

private:
    const ShapeFamilyFactory& factory_;
};

}  // namespace abstract_factory_pattern_classic
