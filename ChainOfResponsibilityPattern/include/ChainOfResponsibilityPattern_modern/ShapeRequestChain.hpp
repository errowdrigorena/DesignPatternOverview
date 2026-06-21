#pragma once

#include <ChainOfResponsibilityPattern_common/ShapeRequest.hpp>

#include <functional>
#include <vector>

namespace chain_of_responsibility_pattern_modern {

class ShapeRequestChain {
public:
    using Handler = std::function<bool(chain_of_responsibility_pattern_common::ShapeRequest&)>;

    void add(Handler handler);
    [[nodiscard]] bool handle(chain_of_responsibility_pattern_common::ShapeRequest& request) const;

private:
    std::vector<Handler> handlers_;
};

}  // namespace chain_of_responsibility_pattern_modern
