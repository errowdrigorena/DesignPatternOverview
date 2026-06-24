#pragma once

#include <Shapes_traditional/Shape.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>

#include <memory>

namespace simple_factory_pseudo_pattern_switch {

class ShapeFactory {
public:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shape> create(
        simple_factory_pseudo_pattern::ShapeType shape_type) const;
};

}  // namespace simple_factory_pseudo_pattern_switch
