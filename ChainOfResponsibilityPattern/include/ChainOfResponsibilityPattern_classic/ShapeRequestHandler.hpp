#pragma once

#include <ChainOfResponsibilityPattern_common/ShapeRequest.hpp>

#include <memory>

namespace chain_of_responsibility_pattern_classic {

using chain_of_responsibility_pattern_common::ShapeOperation;
using chain_of_responsibility_pattern_common::ShapeRequest;

class ShapeRequestHandler {
public:
    virtual ~ShapeRequestHandler() = default;

    void set_successor(std::unique_ptr<ShapeRequestHandler> successor);
    [[nodiscard]] virtual bool handle(ShapeRequest& request) const = 0;

protected:
    [[nodiscard]] bool pass_to_successor(ShapeRequest& request) const;

private:
    std::unique_ptr<ShapeRequestHandler> successor_;
};

}  // namespace chain_of_responsibility_pattern_classic
