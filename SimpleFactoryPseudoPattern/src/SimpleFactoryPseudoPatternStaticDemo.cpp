#include <SimpleFactoryPseudoPattern_static/CircleFactory.hpp>
#include <SimpleFactoryPseudoPattern_static/RectangleFactory.hpp>
#include <SimpleFactoryPseudoPattern_static/ShapeFactory.hpp>
#include <SimpleFactoryPseudoPattern_static/TriangleFactory.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace {

void draw_and_print_area(const shapes_traditional::Shapes& shape)
{
    shape.draw();
    std::cout << "Area: " << shape.calculate_area() << '\n';
}

}  // namespace

int main()
{
    using namespace simple_factory_pseudo_pattern_static;

    std::vector<std::unique_ptr<ShapeFactory>> shape_factories;
    shape_factories.emplace_back(std::make_unique<CircleFactory>());
    shape_factories.emplace_back(std::make_unique<RectangleFactory>());
    shape_factories.emplace_back(std::make_unique<TriangleFactory>());

    for (const auto& shape_factory : shape_factories) {
        const auto shape = shape_factory->create();
        draw_and_print_area(*shape);
    }

    return 0;
}
