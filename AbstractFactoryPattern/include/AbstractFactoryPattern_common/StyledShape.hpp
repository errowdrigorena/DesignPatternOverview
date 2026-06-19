#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <string_view>

namespace abstract_factory_pattern_common {

class StyledShape : public shapes_traditional::Shapes {
public:
    [[nodiscard]] virtual std::string_view family() const = 0;
};

}  // namespace abstract_factory_pattern_common
