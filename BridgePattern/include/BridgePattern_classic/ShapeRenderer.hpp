#pragma once

#include <BridgePattern_common/ShapePath.hpp>

#include <string_view>

namespace bridge_pattern_classic {

class ShapeRenderer {
public:
    virtual ~ShapeRenderer() = default;

    virtual void render(std::string_view shape_name,
                        const bridge_pattern_common::ShapePath& path) const = 0;
};

}  // namespace bridge_pattern_classic
