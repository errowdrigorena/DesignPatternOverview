#include <BridgePattern_modern/Renderers.hpp>

#include <cstddef>
#include <ostream>

namespace bridge_pattern_modern {

Shape::Renderer console_renderer(std::ostream& output)
{
    return [&output](const std::string_view shape_name, const bridge_pattern_common::ShapePath& path) {
        output << "Console " << shape_name << ':';
        for (const bridge_pattern_common::Point& point : path) {
            output << " (" << point.x << ',' << point.y << ')';
        }
        output << '\n';
    };
}

Shape::Renderer svg_renderer(std::ostream& output)
{
    return [&output](const std::string_view shape_name, const bridge_pattern_common::ShapePath& path) {
        output << "<polygon id=\"" << shape_name << "\" points=\"";
        for (std::size_t index = 0; index < path.size(); ++index) {
            const auto& point = path[index];
            if (index != 0U) {
                output << ' ';
            }
            output << point.x << ',' << point.y;
        }
        output << "\"/>\n";
    };
}

}  // namespace bridge_pattern_modern
