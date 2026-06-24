#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <string_view>

namespace abstract_factory_pattern_common {

class StyledShape : public shapes_traditional::Shape {
public:
    [[nodiscard]] virtual std::string_view family() const = 0;
};

}  // namespace abstract_factory_pattern_common
