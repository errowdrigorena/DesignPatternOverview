#include <ChainOfResponsibilityPattern_classic/DrawShapeHandler.hpp>

namespace chain_of_responsibility_pattern_classic {

bool DrawShapeHandler::handle(ShapeRequest& request) const
{
    if (request.operation != ShapeOperation::draw) {
        return pass_to_successor(request);
    }

    request.shape.draw();
    return true;
}

}  // namespace chain_of_responsibility_pattern_classic
