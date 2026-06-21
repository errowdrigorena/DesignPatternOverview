#include <BridgePattern_classic/ConsoleShapeRenderer.hpp>
#include <BridgePattern_classic/RectangleShape.hpp>
#include <BridgePattern_classic/SvgShapeRenderer.hpp>
#include <BridgePattern_classic/TriangleShape.hpp>

#include <iostream>
#include <memory>

int main()
{
    const auto console = std::make_shared<bridge_pattern_classic::ConsoleShapeRenderer>(std::cout);
    const auto svg = std::make_shared<bridge_pattern_classic::SvgShapeRenderer>(std::cout);

    bridge_pattern_classic::RectangleShape rectangle{4.0, 2.0, console};
    bridge_pattern_classic::TriangleShape triangle{6.0, 3.0, svg};

    rectangle.draw();
    triangle.draw();

    rectangle.set_renderer(svg);
    rectangle.draw();
}
