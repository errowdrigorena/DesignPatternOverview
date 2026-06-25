#include <CompositePattern_classic/ShapeGroup.hpp>
#include <CompositePattern_classic/ShapeLeaf.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <stdexcept>

namespace {

using testing::Eq;

using composite_pattern_classic::Graphic;
using composite_pattern_classic::ShapeGroup;
using composite_pattern_classic::ShapeLeaf;

TEST(CompositeClassic, LeafImplementsGraphicInterface)
{
    const ShapeLeaf circle{"Circle", 12.0};

    EXPECT_THAT(circle.area(), Eq(12.0));

    std::ostringstream output;
    circle.render(output);

    EXPECT_THAT(output.str(), Eq("- Circle (12)\n"));
}

TEST(CompositeClassic, GroupAggregatesChildAreas)
{
    ShapeGroup scene{"Scene"};
    scene.add(std::make_unique<ShapeLeaf>("Rectangle", 20.0));
    scene.add(std::make_unique<ShapeLeaf>("Triangle", 15.0));

    EXPECT_THAT(scene.child_count(), Eq(2U));
    EXPECT_THAT(scene.area(), Eq(35.0));
}

TEST(CompositeClassic, NestedGroupsBehaveLikeSingleGraphics)
{
    auto toolbar = std::make_unique<ShapeGroup>("Toolbar");
    toolbar->add(std::make_unique<ShapeLeaf>("Save", 2.0));
    toolbar->add(std::make_unique<ShapeLeaf>("Open", 3.0));

    ShapeGroup screen{"Screen"};
    screen.add(std::make_unique<ShapeLeaf>("Canvas", 40.0));
    screen.add(std::move(toolbar));

    std::ostringstream output;
    screen.render(output);

    EXPECT_THAT(screen.area(), Eq(45.0));
    EXPECT_THAT(output.str(),
                Eq("+ Screen (45)\n"
                   "  - Canvas (40)\n"
                   "  + Toolbar (5)\n"
                   "    - Save (2)\n"
                   "    - Open (3)\n"));
}

TEST(CompositeClassic, CompositeCanBeUsedThroughBasePointer)
{
    std::unique_ptr<Graphic> graphic = std::make_unique<ShapeGroup>("Empty layer");

    EXPECT_THAT(graphic->area(), Eq(0.0));
}

TEST(CompositeClassic, RejectsInvalidChildrenAndShapes)
{
    ShapeGroup group{"Scene"};

    EXPECT_THROW(group.add(nullptr), std::invalid_argument);
    EXPECT_THROW((ShapeLeaf{"", 1.0}), std::invalid_argument);
    EXPECT_THROW((ShapeLeaf{"Broken", -1.0}), std::invalid_argument);
    EXPECT_THROW((ShapeGroup{""}), std::invalid_argument);
}

}  // namespace
