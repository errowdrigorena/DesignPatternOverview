#include <IteratorPattern_boost/ShapeCollection.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <iostream>

int main()
{
    iterator_pattern_boost::ShapeCollection shapes;
    shapes.add(shapes_traditional::Circle::create(3.0));
    shapes.add(shapes_traditional::Rectangle::create(4.0, 2.0));
    shapes.add(shapes_traditional::Triangle::create(6.0, 3.0));

    for (const shapes_traditional::Shape& shape : shapes) {
        std::cout << shape.calculate_area() << '\n';
    }
}
