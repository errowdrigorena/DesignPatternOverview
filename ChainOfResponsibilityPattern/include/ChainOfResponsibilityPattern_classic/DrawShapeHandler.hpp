#pragma once

#include <ChainOfResponsibilityPattern_classic/ShapeRequestHandler.hpp>

namespace chain_of_responsibility_pattern_classic {

class DrawShapeHandler final : public ShapeRequestHandler {
public:
    [[nodiscard]] bool handle(ShapeRequest& request) const override;
};

}  // namespace chain_of_responsibility_pattern_classic
