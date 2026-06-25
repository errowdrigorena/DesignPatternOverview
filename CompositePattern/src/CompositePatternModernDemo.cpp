#include <CompositePattern_modern/GraphicNode.hpp>

#include <iostream>

int main()
{
    using composite_pattern_modern::group;
    using composite_pattern_modern::Node;
    using composite_pattern_modern::render;
    using composite_pattern_modern::shape;

    const Node screen = group(
        "Main screen",
        {
            shape("Canvas", 80.0),
            group("Toolbar icons", {shape("Save icon", 12.0), shape("Open icon", 10.0)}),
        });

    render(screen, std::cout);
}
