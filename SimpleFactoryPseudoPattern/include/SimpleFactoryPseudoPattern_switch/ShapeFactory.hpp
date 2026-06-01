#pragma once

#include <Shapes_traditional/Shapes.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>

#include <memory>

namespace simple_factory_pseudo_pattern_switch {

class ShapeFactory {
public:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shapes> create(
        simple_factory_pseudo_pattern::ShapeType shape_type) const;
};

}  // namespace simple_factory_pseudo_pattern_switch
