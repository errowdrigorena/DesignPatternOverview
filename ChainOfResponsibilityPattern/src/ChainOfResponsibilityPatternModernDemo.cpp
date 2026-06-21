#include <ChainOfResponsibilityPattern_common/ShapeRequest.hpp>
#include <ChainOfResponsibilityPattern_modern/ShapeRequestChain.hpp>

#include <Shapes_traditional/Circle.hpp>

#include <iostream>

int main()
{
    chain_of_responsibility_pattern_modern::ShapeRequestChain chain;
    chain.add([](chain_of_responsibility_pattern_common::ShapeRequest& request) {
        if (request.operation != chain_of_responsibility_pattern_common::ShapeOperation::draw) {
            return false;
        }

        request.shape.draw();
        return true;
    });
    chain.add([](chain_of_responsibility_pattern_common::ShapeRequest& request) {
        if (request.operation != chain_of_responsibility_pattern_common::ShapeOperation::calculate_area) {
            return false;
        }

        request.area = request.shape.calculate_area();
        return true;
    });

    const auto circle = shapes_traditional::Circle::create(3.0);
    chain_of_responsibility_pattern_common::ShapeRequest draw_request{
        *circle,
        chain_of_responsibility_pattern_common::ShapeOperation::draw};
    if (!chain.handle(draw_request)) {
        return 1;
    }

    chain_of_responsibility_pattern_common::ShapeRequest area_request{
        *circle,
        chain_of_responsibility_pattern_common::ShapeOperation::calculate_area};
    if (!chain.handle(area_request)) {
        return 1;
    }

    std::cout << *area_request.area << '\n';
}
