#include <IteratorPattern_classic/ShapeCollection.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <iostream>

int main()
{
    iterator_pattern_classic::ShapeCollection shapes;
    shapes.add(shapes_traditional::Circle::create(3.0));
    shapes.add(shapes_traditional::Rectangle::create(4.0, 2.0));
    shapes.add(shapes_traditional::Triangle::create(6.0, 3.0));

    const auto iterator = shapes.create_iterator();
    for (iterator->first(); !iterator->is_done(); iterator->next()) {
        std::cout << iterator->current_item().calculate_area() << '\n';
    }
}
