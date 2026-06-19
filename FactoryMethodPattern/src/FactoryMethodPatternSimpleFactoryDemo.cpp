#include <FactoryMethodPattern_simple_factory/ShapeScene.hpp>

#include <iostream>

int main()
{
    using simple_factory_pseudo_pattern::ShapeType;

    const factory_method_pattern_simple_factory::ShapeScene scene;
    for (const auto shape_type : {ShapeType::circle, ShapeType::rectangle, ShapeType::triangle}) {
        const auto shape = scene.add_shape(shape_type);
        shape->draw();
        std::cout << "Area: " << shape->calculate_area() << '\n';
    }
}
