#pragma once

#include <BuilderPattern_classic/RectangleBuilder.hpp>

#include <string_view>

namespace builder_pattern_classic {

class RectangleDirector {
public:
    void construct(
        RectangleBuilder& builder,
        std::string_view name,
        double width,
        double height) const;
};

}  // namespace builder_pattern_classic
