#include <Shapes_strategy/ApiDrawStrategy.hpp>
#include <Shapes_strategy/Circle_strategy.hpp>
#include <Shapes_strategy/Rectangle_strategy.hpp>
#include <Shapes_strategy/Shapes.hpp>
#include <Shapes_strategy/StarDrawStrategy.hpp>
#include <Shapes_strategy/Triangle_strategy.hpp>

#include <iostream>
#include <memory>
#include <vector>

int main()
{
    std::vector<std::unique_ptr<shapes_strategy::Shapes>> shapes;
    shapes.push_back(std::make_unique<shapes_strategy::Rectangle_strategy>(
        4.0,
        3.0,
        std::make_unique<shapes_strategy::StarDrawStrategy>()));
    shapes.push_back(std::make_unique<shapes_strategy::Triangle_strategy>(
        4.0,
        3.0,
        std::make_unique<shapes_strategy::StarDrawStrategy>()));
    shapes.push_back(std::make_unique<shapes_strategy::Circle_strategy>(
        2.0,
        std::make_unique<shapes_strategy::StarDrawStrategy>()));

    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->calculate_area() << '\n';
    }

    std::cout << '\n';

    for (const auto& shape : shapes) {
        shape->set_strategy(std::make_unique<shapes_strategy::ApiDrawStrategy>());
        shape->draw();
    }

    return 0;
}
