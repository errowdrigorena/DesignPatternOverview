#include <BridgePattern_modern/Renderers.hpp>
#include <BridgePattern_modern/Shape.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

namespace {

TEST(BridgeModern, RectangleUsesConsoleRenderer)
{
    std::ostringstream output;
    const auto rectangle = bridge_pattern_modern::Shape::rectangle(
        4.0,
        2.0,
        bridge_pattern_modern::console_renderer(output));

    rectangle.draw();

    EXPECT_EQ(output.str(), "Console rectangle: (0,0) (4,0) (4,2) (0,2)\n");
}

TEST(BridgeModern, TriangleUsesSvgRenderer)
{
    std::ostringstream output;
    const auto triangle = bridge_pattern_modern::Shape::triangle(
        6.0,
        3.0,
        bridge_pattern_modern::svg_renderer(output));

    triangle.draw();

    EXPECT_EQ(output.str(), "<polygon id=\"triangle\" points=\"0,3 3,0 6,3\"/>\n");
}

TEST(BridgeModern, OneRendererSupportsSeveralShapes)
{
    std::ostringstream output;
    const auto console = bridge_pattern_modern::console_renderer(output);
    const auto rectangle = bridge_pattern_modern::Shape::rectangle(4.0, 2.0, console);
    const auto triangle = bridge_pattern_modern::Shape::triangle(6.0, 3.0, console);

    rectangle.draw();
    triangle.draw();

    EXPECT_EQ(output.str(),
              "Console rectangle: (0,0) (4,0) (4,2) (0,2)\n"
              "Console triangle: (0,3) (3,0) (6,3)\n");
}

TEST(BridgeModern, OneShapeCanChangeRendererAtRuntime)
{
    std::ostringstream console_output;
    std::ostringstream svg_output;
    auto rectangle = bridge_pattern_modern::Shape::rectangle(
        4.0,
        2.0,
        bridge_pattern_modern::console_renderer(console_output));

    rectangle.draw();
    rectangle.set_renderer(bridge_pattern_modern::svg_renderer(svg_output));
    rectangle.draw();

    EXPECT_EQ(console_output.str(), "Console rectangle: (0,0) (4,0) (4,2) (0,2)\n");
    EXPECT_EQ(svg_output.str(), "<polygon id=\"rectangle\" points=\"0,0 4,0 4,2 0,2\"/>\n");
}

TEST(BridgeModern, ShapesRejectEmptyRenderers)
{
    EXPECT_THROW(static_cast<void>(bridge_pattern_modern::Shape::rectangle(4.0, 2.0, {})),
                 std::invalid_argument);

    std::ostringstream output;
    auto rectangle = bridge_pattern_modern::Shape::rectangle(
        4.0,
        2.0,
        bridge_pattern_modern::console_renderer(output));

    EXPECT_THROW(rectangle.set_renderer({}), std::invalid_argument);
}

}  // namespace
