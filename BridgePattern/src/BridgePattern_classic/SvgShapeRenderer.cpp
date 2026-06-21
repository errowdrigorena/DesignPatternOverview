#include <BridgePattern_classic/SvgShapeRenderer.hpp>

#include <cstddef>
#include <ostream>

namespace bridge_pattern_classic {

SvgShapeRenderer::SvgShapeRenderer(std::ostream& output)
    : output_{output}
{
}

void SvgShapeRenderer::render(const std::string_view shape_name,
                              const bridge_pattern_common::ShapePath& path) const
{
    output_ << "<polygon id=\"" << shape_name << "\" points=\"";
    for (std::size_t index = 0; index < path.size(); ++index) {
        const auto& point = path[index];
        if (index != 0U) {
            output_ << ' ';
        }
        output_ << point.x << ',' << point.y;
    }
    output_ << "\"/>\n";
}

}  // namespace bridge_pattern_classic
