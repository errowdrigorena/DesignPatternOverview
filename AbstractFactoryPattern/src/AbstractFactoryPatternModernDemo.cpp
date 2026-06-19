#include <AbstractFactoryPattern_modern/ShapeFamilyFactory.hpp>
#include <AbstractFactoryPattern_modern/ShapeScene.hpp>

#include <iostream>

int main()
{
    for (const auto factory : {
             abstract_factory_pattern_modern::make_wireframe_shape_factory(),
             abstract_factory_pattern_modern::make_solid_shape_factory(),
         }) {
        const abstract_factory_pattern_modern::ShapeScene scene{factory};
        std::cout << factory.family << " family\n";
        for (const auto& shape : scene.create_sample_scene()) {
            shape->draw();
        }
        std::cout << "Total area: " << scene.sample_scene_area() << '\n';
    }
}
