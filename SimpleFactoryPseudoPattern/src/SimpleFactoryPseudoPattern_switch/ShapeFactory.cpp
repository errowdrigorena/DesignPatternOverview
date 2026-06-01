#include <SimpleFactoryPseudoPattern_switch/ShapeFactory.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <stdexcept>

namespace simple_factory_pseudo_pattern_switch {

std::unique_ptr<shapes_traditional::Shapes> ShapeFactory::create(
    const simple_factory_pseudo_pattern::ShapeType shape_type) const
{
    switch (shape_type) {
    case simple_factory_pseudo_pattern::ShapeType::circle:
        return std::make_unique<shapes_traditional::Circle>(6.0);
    case simple_factory_pseudo_pattern::ShapeType::rectangle:
        return std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0);
    case simple_factory_pseudo_pattern::ShapeType::triangle:
        return std::make_unique<shapes_traditional::Triangle>(4.0, 3.0);
    }

    throw std::invalid_argument{"unknown shape type"};
}

}  // namespace simple_factory_pseudo_pattern_switch
