#include <ChainOfResponsibilityPattern_classic/AreaShapeHandler.hpp>

namespace chain_of_responsibility_pattern_classic {

bool AreaShapeHandler::handle(ShapeRequest& request) const
{
    if (request.operation != ShapeOperation::calculate_area) {
        return pass_to_successor(request);
    }

    request.area = request.shape.calculate_area();
    return true;
}

}  // namespace chain_of_responsibility_pattern_classic
