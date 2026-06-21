#include <ChainOfResponsibilityPattern_classic/ShapeRequestHandler.hpp>

#include <utility>

namespace chain_of_responsibility_pattern_classic {

void ShapeRequestHandler::set_successor(std::unique_ptr<ShapeRequestHandler> successor)
{
    successor_ = std::move(successor);
}

bool ShapeRequestHandler::pass_to_successor(ShapeRequest& request) const
{
    return successor_ && successor_->handle(request);
}

}  // namespace chain_of_responsibility_pattern_classic
