#include <BridgePattern_classic/ConsoleShapeRenderer.hpp>
#include <BridgePattern_classic/RectangleShape.hpp>
#include <BridgePattern_classic/SvgShapeRenderer.hpp>
#include <BridgePattern_classic/TriangleShape.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <stdexcept>

namespace {

TEST(BridgeClassic, RectangleUsesConsoleRenderer)
{
    std::ostringstream output;
    const auto console = std::make_shared<bridge_pattern_classic::ConsoleShapeRenderer>(output);
    bridge_pattern_classic::RectangleShape rectangle{4.0, 2.0, console};

    rectangle.draw();

    EXPECT_EQ(output.str(), "Console rectangle: (0,0) (4,0) (4,2) (0,2)\n");
}

TEST(BridgeClassic, TriangleUsesSvgRenderer)
{
    std::ostringstream output;
    const auto svg = std::make_shared<bridge_pattern_classic::SvgShapeRenderer>(output);
    bridge_pattern_classic::TriangleShape triangle{6.0, 3.0, svg};

    triangle.draw();

    EXPECT_EQ(output.str(), "<polygon id=\"triangle\" points=\"0,3 3,0 6,3\"/>\n");
}

TEST(BridgeClassic, OneRendererSupportsSeveralShapeAbstractions)
{
    std::ostringstream output;
    const auto console = std::make_shared<bridge_pattern_classic::ConsoleShapeRenderer>(output);
    bridge_pattern_classic::RectangleShape rectangle{4.0, 2.0, console};
    bridge_pattern_classic::TriangleShape triangle{6.0, 3.0, console};

    rectangle.draw();
    triangle.draw();

    EXPECT_EQ(output.str(),
              "Console rectangle: (0,0) (4,0) (4,2) (0,2)\n"
              "Console triangle: (0,3) (3,0) (6,3)\n");
}

TEST(BridgeClassic, OneShapeCanChangeRendererAtRuntime)
{
    std::ostringstream console_output;
    std::ostringstream svg_output;
    const auto console = std::make_shared<bridge_pattern_classic::ConsoleShapeRenderer>(console_output);
    const auto svg = std::make_shared<bridge_pattern_classic::SvgShapeRenderer>(svg_output);
    bridge_pattern_classic::RectangleShape rectangle{4.0, 2.0, console};

    rectangle.draw();
    rectangle.set_renderer(svg);
    rectangle.draw();

    EXPECT_EQ(console_output.str(), "Console rectangle: (0,0) (4,0) (4,2) (0,2)\n");
    EXPECT_EQ(svg_output.str(), "<polygon id=\"rectangle\" points=\"0,0 4,0 4,2 0,2\"/>\n");
}

TEST(BridgeClassic, ShapesRejectMissingRenderers)
{
    EXPECT_THROW((bridge_pattern_classic::RectangleShape{4.0, 2.0, nullptr}), std::invalid_argument);

    std::ostringstream output;
    const auto console = std::make_shared<bridge_pattern_classic::ConsoleShapeRenderer>(output);
    bridge_pattern_classic::RectangleShape rectangle{4.0, 2.0, console};

    EXPECT_THROW(rectangle.set_renderer(nullptr), std::invalid_argument);
}

}  // namespace
