#include <PrototypePattern_modern/CirclePrototype.hpp>
#include <PrototypePattern_modern/RectanglePrototype.hpp>
#include <PrototypePattern_modern/ShapePrototype.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <vector>

namespace {

std::string describe(const prototype_pattern_modern::ShapePrototype& prototype)
{
    std::ostringstream output;
    prototype.draw(output);
    return output.str();
}

TEST(ModernPrototype, DrawsACirclePrototype)
{
    const prototype_pattern_modern::CirclePrototype prototype{
        "port",
        "green",
        12.0,
        16.0,
        8.0};

    EXPECT_EQ(describe(prototype), "CirclePrototype{name=port, color=green, x=12, y=16, radius=8}\n");
}

TEST(ModernPrototype, DrawsARectanglePrototype)
{
    const prototype_pattern_modern::RectanglePrototype prototype{
        "node",
        "green",
        0.0,
        0.0,
        96.0,
        48.0};

    EXPECT_EQ(describe(prototype), "RectanglePrototype{name=node, color=green, x=0, y=0, width=96, height=48}\n");
}

TEST(ModernPrototype, CloneReturnsOwningPointer)
{
    const prototype_pattern_modern::CirclePrototype original{
        "port",
        "green",
        12.0,
        16.0,
        8.0};

    const std::unique_ptr<prototype_pattern_modern::ShapePrototype> clone = original.clone();

    EXPECT_EQ(describe(*clone), "CirclePrototype{name=port, color=green, x=12, y=16, radius=8}\n");
}

TEST(ModernPrototype, MutatingCloneDoesNotChangeOriginal)
{
    const prototype_pattern_modern::RectanglePrototype original{
        "node",
        "green",
        0.0,
        0.0,
        96.0,
        48.0};
    const auto clone = original.clone();

    clone->set_name("selected-node");
    clone->set_color("purple");
    clone->move_to(32.0, 24.0);

    EXPECT_EQ(describe(original), "RectanglePrototype{name=node, color=green, x=0, y=0, width=96, height=48}\n");
    EXPECT_EQ(
        describe(*clone),
        "RectanglePrototype{name=selected-node, color=purple, x=32, y=24, width=96, height=48}\n");
}

TEST(ModernPrototype, ClonesDifferentConcreteShapesThroughTheBaseType)
{
    std::vector<std::unique_ptr<prototype_pattern_modern::ShapePrototype>> palette;
    palette.push_back(std::make_unique<prototype_pattern_modern::CirclePrototype>(
        "port",
        "green",
        0.0,
        0.0,
        8.0));
    palette.push_back(std::make_unique<prototype_pattern_modern::RectanglePrototype>(
        "node",
        "green",
        0.0,
        0.0,
        96.0,
        48.0));

    std::vector<std::unique_ptr<prototype_pattern_modern::ShapePrototype>> diagram_shapes;
    for (const auto& prototype : palette) {
        auto shape = prototype->clone();
        shape->set_color("purple");
        shape->move_to(32.0, 24.0);
        diagram_shapes.push_back(std::move(shape));
    }

    EXPECT_EQ(describe(*palette[0]), "CirclePrototype{name=port, color=green, x=0, y=0, radius=8}\n");
    EXPECT_EQ(describe(*palette[1]), "RectanglePrototype{name=node, color=green, x=0, y=0, width=96, height=48}\n");
    EXPECT_EQ(describe(*diagram_shapes[0]), "CirclePrototype{name=port, color=purple, x=32, y=24, radius=8}\n");
    EXPECT_EQ(
        describe(*diagram_shapes[1]),
        "RectanglePrototype{name=node, color=purple, x=32, y=24, width=96, height=48}\n");
}

}  // namespace
