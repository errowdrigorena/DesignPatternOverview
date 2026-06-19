#include <AbstractFactoryPattern_classic/ShapeScene.hpp>

#include <numeric>

namespace abstract_factory_pattern_classic {

ShapeScene::ShapeScene(const ShapeFamilyFactory& factory)
    : factory_{factory}
{
}

ShapeCollection ShapeScene::create_sample_scene(
    const double circle_radius,
    const double rectangle_width,
    const double rectangle_height,
    const double triangle_base,
    const double triangle_height) const
{
    ShapeCollection shapes;
    shapes.push_back(factory_.create_circle(circle_radius));
    shapes.push_back(factory_.create_rectangle(rectangle_width, rectangle_height));
    shapes.push_back(factory_.create_triangle(triangle_base, triangle_height));
    return shapes;
}

double ShapeScene::sample_scene_area(
    const double circle_radius,
    const double rectangle_width,
    const double rectangle_height,
    const double triangle_base,
    const double triangle_height) const
{
    const auto shapes = create_sample_scene(
        circle_radius,
        rectangle_width,
        rectangle_height,
        triangle_base,
        triangle_height);
    return std::accumulate(
        shapes.begin(),
        shapes.end(),
        0.0,
        [](const double total, const auto& shape) {
            return total + shape->calculate_area();
        });
}

}  // namespace abstract_factory_pattern_classic
