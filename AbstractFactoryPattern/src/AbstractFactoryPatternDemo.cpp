#include <AbstractFactoryPattern_classic/SolidShapeFactory.hpp>
#include <AbstractFactoryPattern_classic/WireframeShapeFactory.hpp>
#include <AbstractFactoryPattern_classic/ShapeScene.hpp>

#include <iostream>

namespace {

void render_scene(
    const char* title,
    const abstract_factory_pattern_classic::ShapeFamilyFactory& factory)
{
    const abstract_factory_pattern_classic::ShapeScene scene{factory};
    std::cout << title << '\n';
    for (const auto& shape : scene.create_sample_scene()) {
        shape->draw();
    }
    std::cout << "Total area: " << scene.sample_scene_area() << '\n';
}

}  // namespace

int main()
{
    const abstract_factory_pattern_classic::WireframeShapeFactory wireframe_factory;
    const abstract_factory_pattern_classic::SolidShapeFactory solid_factory;

    render_scene("Wireframe family", wireframe_factory);
    render_scene("Solid family", solid_factory);
}
