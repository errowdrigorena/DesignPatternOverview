#pragma once

#include <FactoryMethodPattern_modern/DynamicFactory.hpp>
#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Shapes.hpp>
#include <Shapes_traditional/Triangle.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>

namespace factory_method_pattern_modern {

class ShapeRegistry {
public:
    ShapeRegistry()
    {
        registry_.register_creator(
            simple_factory_pseudo_pattern::ShapeType::circle,
            [] -> std::unique_ptr<shapes_traditional::Shapes> {
                return std::make_unique<shapes_traditional::Circle>(6.0);
            });
        registry_.register_creator(
            simple_factory_pseudo_pattern::ShapeType::rectangle,
            [] -> std::unique_ptr<shapes_traditional::Shapes> {
                return std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0);
            });
        registry_.register_creator(
            simple_factory_pseudo_pattern::ShapeType::triangle,
            [] -> std::unique_ptr<shapes_traditional::Shapes> {
                return std::make_unique<shapes_traditional::Triangle>(4.0, 3.0);
            });
    }

    [[nodiscard]] std::unique_ptr<shapes_traditional::Shapes> create(
        simple_factory_pseudo_pattern::ShapeType shape_type) const
    {
        return registry_.create(shape_type);
    }

private:
    DynamicFactory<shapes_traditional::Shapes, simple_factory_pseudo_pattern::ShapeType> registry_;
};

}  // namespace factory_method_pattern_modern
