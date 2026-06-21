#include <ChainOfResponsibilityPattern_modern/ShapeRequestChain.hpp>

#include <stdexcept>
#include <utility>

namespace chain_of_responsibility_pattern_modern {

void ShapeRequestChain::add(Handler handler)
{
    if (!handler) {
        throw std::invalid_argument("A request chain cannot contain an empty handler");
    }

    handlers_.push_back(std::move(handler));
}

bool ShapeRequestChain::handle(chain_of_responsibility_pattern_common::ShapeRequest& request) const
{
    for (const Handler& handler : handlers_) {
        if (handler(request)) {
            return true;
        }
    }

    return false;
}

}  // namespace chain_of_responsibility_pattern_modern
