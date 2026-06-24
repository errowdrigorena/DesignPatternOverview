#include <SimpleFactoryPseudoPattern_map/ShapeFactory.hpp>

#include <iostream>

namespace {

void draw_and_print_area(const shapes_traditional::Shape& shape)
{
    shape.draw();
    std::cout << "Area: " << shape.calculate_area() << '\n';
}

}  // namespace

int main()
{
    const simple_factory_pseudo_pattern_map::ShapeFactory shape_factory;

    const auto circle = shape_factory.create("circle");
    const auto rectangle = shape_factory.create("rectangle");
    const auto triangle = shape_factory.create("triangle");

    draw_and_print_area(*circle);
    draw_and_print_area(*rectangle);
    draw_and_print_area(*triangle);

    return 0;
}
