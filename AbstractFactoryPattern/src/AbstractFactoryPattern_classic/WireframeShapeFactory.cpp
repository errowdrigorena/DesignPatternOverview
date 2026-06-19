#include <AbstractFactoryPattern_classic/WireframeShapeFactory.hpp>

#include <AbstractFactoryPattern_common/WireframeShapes/WireframeShapes.hpp>

namespace abstract_factory_pattern_classic {

std::unique_ptr<shapes_traditional::Shapes> WireframeShapeFactory::create_circle(
    const double radius) const
{
    return std::make_unique<abstract_factory_pattern_common::WireframeCircle>(radius);
}

std::unique_ptr<shapes_traditional::Shapes> WireframeShapeFactory::create_rectangle(
    const double width,
    const double height) const
{
    return std::make_unique<abstract_factory_pattern_common::WireframeRectangle>(width, height);
}

std::unique_ptr<shapes_traditional::Shapes> WireframeShapeFactory::create_triangle(
    const double base,
    const double height) const
{
    return std::make_unique<abstract_factory_pattern_common::WireframeTriangle>(base, height);
}

}  // namespace abstract_factory_pattern_classic
