#include <PrototypePattern_classic/CirclePrototype.hpp>
#include <PrototypePattern_classic/RectanglePrototype.hpp>
#include <PrototypePattern_classic/ShapePrototype.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <sstream>

namespace {

std::string describe(const prototype_pattern_classic::ShapePrototype& prototype)
{
    std::ostringstream output;
    prototype.draw(output);
    return output.str();
}

TEST(ClassicPrototype, DrawsACirclePrototype)
{
    const prototype_pattern_classic::CirclePrototype prototype{
        "selection-handle",
        "blue",
        10.0,
        20.0,
        6.0};

    EXPECT_EQ(
        describe(prototype),
        "CirclePrototype{name=selection-handle, color=blue, x=10, y=20, radius=6}\n");
}

TEST(ClassicPrototype, DrawsARectanglePrototype)
{
    const prototype_pattern_classic::RectanglePrototype prototype{
        "selection-box",
        "blue",
        4.0,
        8.0,
        120.0,
        80.0};

    EXPECT_EQ(
        describe(prototype),
        "RectanglePrototype{name=selection-box, color=blue, x=4, y=8, width=120, height=80}\n");
}

TEST(ClassicPrototype, CloneCopiesCurrentState)
{
    const prototype_pattern_classic::CirclePrototype original{
        "port",
        "green",
        12.0,
        16.0,
        8.0};

    const std::unique_ptr<prototype_pattern_classic::ShapePrototype> clone{original.clone()};

    EXPECT_EQ(describe(*clone), "CirclePrototype{name=port, color=green, x=12, y=16, radius=8}\n");
}

TEST(ClassicPrototype, MutatingCloneDoesNotChangeOriginal)
{
    const prototype_pattern_classic::RectanglePrototype original{
        "node",
        "green",
        0.0,
        0.0,
        96.0,
        48.0};
    const std::unique_ptr<prototype_pattern_classic::ShapePrototype> clone{original.clone()};

    clone->set_name("selected-node");
    clone->set_color("purple");
    clone->move_to(32.0, 24.0);

    EXPECT_EQ(describe(original), "RectanglePrototype{name=node, color=green, x=0, y=0, width=96, height=48}\n");
    EXPECT_EQ(
        describe(*clone),
        "RectanglePrototype{name=selected-node, color=purple, x=32, y=24, width=96, height=48}\n");
}

}  // namespace
