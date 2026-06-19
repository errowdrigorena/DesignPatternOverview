#include <AbstractFactoryPattern_classic/SolidShapeFactory.hpp>

#include <AbstractFactoryPattern_common/SolidShapes/SolidShapes.hpp>

namespace abstract_factory_pattern_classic {

std::unique_ptr<shapes_traditional::Shapes> SolidShapeFactory::create_circle(
    const double radius) const
{
    return std::make_unique<abstract_factory_pattern_common::SolidCircle>(radius);
}

std::unique_ptr<shapes_traditional::Shapes> SolidShapeFactory::create_rectangle(
    const double width,
    const double height) const
{
    return std::make_unique<abstract_factory_pattern_common::SolidRectangle>(width, height);
}

std::unique_ptr<shapes_traditional::Shapes> SolidShapeFactory::create_triangle(
    const double base,
    const double height) const
{
    return std::make_unique<abstract_factory_pattern_common::SolidTriangle>(base, height);
}

}  // namespace abstract_factory_pattern_classic
