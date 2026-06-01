#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <memory>
#include <string_view>

namespace simple_factory_pseudo_pattern_map {

class ShapeFactory {
public:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shapes> create(
        std::string_view shape_name) const;
};

}  // namespace simple_factory_pseudo_pattern_map
