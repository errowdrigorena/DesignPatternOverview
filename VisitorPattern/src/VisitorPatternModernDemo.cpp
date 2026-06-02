#include <VisitorPattern_modern/AreaVisitor.hpp>
#include <VisitorPattern_modern/DrawVisitor.hpp>
#include <VisitorPattern_modern/Shape.hpp>

#include <iostream>
#include <variant>
#include <vector>

int main()
{
    using namespace visitor_pattern_modern;

    const std::vector<Shape> shapes{
        Circle{6.0},
        Rectangle{4.0, 3.0},
        Triangle{4.0, 3.0},
    };

    const DrawVisitor draw_visitor{std::cout};
    const AreaVisitor area_visitor;

    for (const auto& shape : shapes) {
        std::visit(draw_visitor, shape);
        std::cout << "Area: " << std::visit(area_visitor, shape) << '\n';
    }

    return 0;
}
