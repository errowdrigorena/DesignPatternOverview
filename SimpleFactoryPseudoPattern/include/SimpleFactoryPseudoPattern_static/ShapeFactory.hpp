#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <memory>

namespace simple_factory_pseudo_pattern_static {

class ShapeFactory {
public:
    virtual ~ShapeFactory() = default;

    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shapes> create() const = 0;
};

}  // namespace simple_factory_pseudo_pattern_static
