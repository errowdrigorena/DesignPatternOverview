#include <AbstractFactoryPattern_modern/ShapeFamilyFactory.hpp>

#include <AbstractFactoryPattern_common/SolidShapes/SolidShapes.hpp>
#include <AbstractFactoryPattern_common/WireframeShapes/WireframeShapes.hpp>

namespace abstract_factory_pattern_modern {

ShapeFamilyFactory make_wireframe_shape_factory()
{
    return ShapeFamilyFactory{
        .family = "wireframe",
        .create_circle = [](const double radius) {
            return std::make_unique<abstract_factory_pattern_common::WireframeCircle>(
                radius);
        },
        .create_rectangle = [](const double width, const double height) {
            return std::make_unique<abstract_factory_pattern_common::WireframeRectangle>(
                width,
                height);
        },
        .create_triangle = [](const double base, const double height) {
            return std::make_unique<abstract_factory_pattern_common::WireframeTriangle>(
                base,
                height);
        },
    };
}

ShapeFamilyFactory make_solid_shape_factory()
{
    return ShapeFamilyFactory{
        .family = "solid",
        .create_circle = [](const double radius) {
            return std::make_unique<abstract_factory_pattern_common::SolidCircle>(
                radius);
        },
        .create_rectangle = [](const double width, const double height) {
            return std::make_unique<abstract_factory_pattern_common::SolidRectangle>(
                width,
                height);
        },
        .create_triangle = [](const double base, const double height) {
            return std::make_unique<abstract_factory_pattern_common::SolidTriangle>(
                base,
                height);
        },
    };
}

}  // namespace abstract_factory_pattern_modern
