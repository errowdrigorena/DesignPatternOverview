#pragma once

#include <BridgePattern_common/ShapePath.hpp>

#include <functional>
#include <string>
#include <string_view>

namespace bridge_pattern_modern {

class Shape {
public:
    using Renderer = std::function<void(std::string_view, const bridge_pattern_common::ShapePath&)>;

    Shape(std::string name, bridge_pattern_common::ShapePath path, Renderer renderer);

    [[nodiscard]] static Shape rectangle(double width, double height, Renderer renderer);
    [[nodiscard]] static Shape triangle(double base, double height, Renderer renderer);

    void set_renderer(Renderer renderer);
    void draw() const;

private:
    std::string name_;
    bridge_pattern_common::ShapePath path_;
    Renderer renderer_;
};

}  // namespace bridge_pattern_modern
