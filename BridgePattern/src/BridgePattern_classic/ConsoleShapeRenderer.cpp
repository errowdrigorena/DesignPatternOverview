#include <BridgePattern_classic/ConsoleShapeRenderer.hpp>

#include <ostream>

namespace bridge_pattern_classic {

ConsoleShapeRenderer::ConsoleShapeRenderer(std::ostream& output)
    : output_{output}
{
}

void ConsoleShapeRenderer::render(const std::string_view shape_name,
                                  const bridge_pattern_common::ShapePath& path) const
{
    output_ << "Console " << shape_name << ':';
    for (const bridge_pattern_common::Point& point : path) {
        output_ << " (" << point.x << ',' << point.y << ')';
    }
    output_ << '\n';
}

}  // namespace bridge_pattern_classic
