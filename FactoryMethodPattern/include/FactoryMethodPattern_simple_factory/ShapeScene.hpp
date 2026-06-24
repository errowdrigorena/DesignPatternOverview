#pragma once

#include <Shapes_traditional/Shape.hpp>
#include <SimpleFactoryPseudoPattern_common/ShapeType.hpp>
#include <SimpleFactoryPseudoPattern_switch/ShapeFactory.hpp>

#include <memory>

namespace factory_method_pattern_simple_factory {

class ShapeScene {
public:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shape> add_shape(
        simple_factory_pseudo_pattern::ShapeType shape_type) const
    {
        return factory_.create(shape_type);
    }

    [[nodiscard]] double preview_area(simple_factory_pseudo_pattern::ShapeType shape_type) const
    {
        return add_shape(shape_type)->calculate_area();
    }

private:
    simple_factory_pseudo_pattern_switch::ShapeFactory factory_;
};

}  // namespace factory_method_pattern_simple_factory
