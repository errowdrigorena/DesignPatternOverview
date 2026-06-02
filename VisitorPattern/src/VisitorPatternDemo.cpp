#include <VisitorPattern_classic/AreaVisitor.hpp>
#include <VisitorPattern_classic/Circle.hpp>
#include <VisitorPattern_classic/DrawVisitor.hpp>
#include <VisitorPattern_classic/Rectangle.hpp>
#include <VisitorPattern_classic/Shape.hpp>
#include <VisitorPattern_classic/Triangle.hpp>

#include <iostream>
#include <memory>
#include <vector>

int main()
{
    using namespace visitor_pattern_classic;

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Circle>(6.0));
    shapes.emplace_back(std::make_unique<Rectangle>(4.0, 3.0));
    shapes.emplace_back(std::make_unique<Triangle>(4.0, 3.0));

    DrawVisitor draw_visitor{std::cout};

    for (const auto& shape : shapes) {
        AreaVisitor area_visitor;

        shape->accept(draw_visitor);
        shape->accept(area_visitor);

        std::cout << "Area: " << area_visitor.area() << '\n';
    }

    return 0;
}
