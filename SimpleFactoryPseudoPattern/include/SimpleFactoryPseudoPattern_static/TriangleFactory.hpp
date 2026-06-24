#pragma once

#include <SimpleFactoryPseudoPattern_static/ShapeFactory.hpp>

namespace simple_factory_pseudo_pattern_static {

class TriangleFactory final : public ShapeFactory {
public:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shape> create() const override;
};

}  // namespace simple_factory_pseudo_pattern_static
