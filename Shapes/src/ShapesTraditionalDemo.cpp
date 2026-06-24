#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Shape.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <iostream>
#include <memory>
#include <vector>

int main()
{
    std::vector<std::unique_ptr<shapes_traditional::Shape>> shapes;
    shapes.push_back(std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0));
    shapes.push_back(std::make_unique<shapes_traditional::Triangle>(4.0, 3.0));
    shapes.push_back(std::make_unique<shapes_traditional::Circle>(2.0));

    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->calculate_area() << '\n';
    }

    return 0;
}
