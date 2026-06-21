#include <BridgePattern_modern/Renderers.hpp>
#include <BridgePattern_modern/Shape.hpp>

#include <iostream>

int main()
{
    const auto console = bridge_pattern_modern::console_renderer(std::cout);
    const auto svg = bridge_pattern_modern::svg_renderer(std::cout);

    auto rectangle = bridge_pattern_modern::Shape::rectangle(4.0, 2.0, console);
    const auto triangle = bridge_pattern_modern::Shape::triangle(6.0, 3.0, svg);

    rectangle.draw();
    triangle.draw();

    rectangle.set_renderer(svg);
    rectangle.draw();
}
