#include <ChainOfResponsibilityPattern_classic/AreaShapeHandler.hpp>
#include <ChainOfResponsibilityPattern_classic/DrawShapeHandler.hpp>
#include <ChainOfResponsibilityPattern_common/ShapeRequest.hpp>

#include <Shapes_traditional/Circle.hpp>

#include <iostream>
#include <memory>

int main()
{
    chain_of_responsibility_pattern_classic::DrawShapeHandler first_handler;
    first_handler.set_successor(
        std::make_unique<chain_of_responsibility_pattern_classic::AreaShapeHandler>());

    const auto circle = shapes_traditional::Circle::create(3.0);

    chain_of_responsibility_pattern_common::ShapeRequest draw_request{
        *circle,
        chain_of_responsibility_pattern_common::ShapeOperation::draw};
    if (!first_handler.handle(draw_request)) {
        return 1;
    }

    chain_of_responsibility_pattern_common::ShapeRequest area_request{
        *circle,
        chain_of_responsibility_pattern_common::ShapeOperation::calculate_area};
    if (!first_handler.handle(area_request)) {
        return 1;
    }

    std::cout << *area_request.area << '\n';
}
