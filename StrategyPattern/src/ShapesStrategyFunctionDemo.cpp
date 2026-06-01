#include <Shapes_strategy_function/Circle.hpp>
#include <Shapes_strategy_function/DrawStrategies.hpp>
#include <Shapes_strategy_function/Rectangle.hpp>
#include <Shapes_strategy_function/Triangle.hpp>

#include <iostream>

int main()
{
    shapes_strategy_function::Rectangle rectangle{
        4.0,
        3.0,
        shapes_strategy_function::draw_rectangle_with_stars};
    shapes_strategy_function::Triangle triangle{
        4.0,
        3.0,
        shapes_strategy_function::draw_triangle_with_stars};
    shapes_strategy_function::Circle circle{
        6.0,
        shapes_strategy_function::draw_circle_with_stars};

    rectangle.draw();
    std::cout << "Area: " << rectangle.calculate_area() << '\n';

    triangle.draw();
    std::cout << "Area: " << triangle.calculate_area() << '\n';

    circle.draw();
    std::cout << "Area: " << circle.calculate_area() << '\n';

    std::cout << '\n';

    rectangle.set_strategy(shapes_strategy_function::send_rectangle_to_api);
    triangle.set_strategy(shapes_strategy_function::send_triangle_to_api);
    circle.set_strategy(shapes_strategy_function::send_circle_to_api);

    rectangle.draw();
    triangle.draw();
    circle.draw();

    return 0;
}
