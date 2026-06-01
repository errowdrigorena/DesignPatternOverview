#include <Shapes_modern/Circle.hpp>
#include <Shapes_modern/Rectangle.hpp>
#include <Shapes_modern/Triangle.hpp>

#include <iostream>

int main()
{
    const shapes_modern::Rectangle rectangle{4.0, 3.0};
    const shapes_modern::Triangle triangle{4.0, 3.0};
    const shapes_modern::Circle circle{2.0};

    rectangle.draw();
    std::cout << "Area: " << rectangle.calculate_area() << '\n';

    triangle.draw();
    std::cout << "Area: " << triangle.calculate_area() << '\n';

    circle.draw();
    std::cout << "Area: " << circle.calculate_area() << '\n';

    return 0;
}
