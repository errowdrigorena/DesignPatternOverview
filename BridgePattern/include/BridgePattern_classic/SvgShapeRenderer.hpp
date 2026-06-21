#pragma once

#include <BridgePattern_classic/ShapeRenderer.hpp>

#include <iosfwd>

namespace bridge_pattern_classic {

class SvgShapeRenderer final : public ShapeRenderer {
public:
    explicit SvgShapeRenderer(std::ostream& output);

    void render(std::string_view shape_name,
                const bridge_pattern_common::ShapePath& path) const override;

private:
    std::ostream& output_;
};

}  // namespace bridge_pattern_classic
