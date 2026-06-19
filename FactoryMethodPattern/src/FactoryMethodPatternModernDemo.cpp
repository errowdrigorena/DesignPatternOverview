#include <FactoryMethodPattern_modern/ShapeRegistry.hpp>

#include <iostream>

int main()
{
    using simple_factory_pseudo_pattern::ShapeType;

    const factory_method_pattern_modern::ShapeRegistry registry;
    for (const auto shape_type : {ShapeType::circle, ShapeType::rectangle, ShapeType::triangle}) {
        const auto shape = registry.create(shape_type);
        shape->draw();
        std::cout << "Area: " << shape->calculate_area() << '\n';
    }
}
