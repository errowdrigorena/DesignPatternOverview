#pragma once

#include <BridgePattern_modern/Shape.hpp>

#include <iosfwd>

namespace bridge_pattern_modern {

[[nodiscard]] Shape::Renderer console_renderer(std::ostream& output);
[[nodiscard]] Shape::Renderer svg_renderer(std::ostream& output);

}  // namespace bridge_pattern_modern
