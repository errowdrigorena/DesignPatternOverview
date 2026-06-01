#include <SimpleFactoryPseudoPattern_template/ShapeFactory.hpp>

#include <iostream>

namespace {

void draw_and_print_area(const shapes_traditional::Shapes& shape)
{
    shape.draw();
    std::cout << "Area: " << shape.calculate_area() << '\n';
}

}  // namespace

int main()
{
    const auto circle =
        simple_factory_pseudo_pattern_template::ShapeFactory<
            simple_factory_pseudo_pattern_template::CircleTag>::create();
    const auto rectangle =
        simple_factory_pseudo_pattern_template::ShapeFactory<
            simple_factory_pseudo_pattern_template::RectangleTag>::create();
    const auto triangle =
        simple_factory_pseudo_pattern_template::ShapeFactory<
            simple_factory_pseudo_pattern_template::TriangleTag>::create();

    draw_and_print_area(*circle);
    draw_and_print_area(*rectangle);
    draw_and_print_area(*triangle);

    return 0;
}
