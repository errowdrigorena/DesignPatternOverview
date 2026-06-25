#include <CompositePattern_modern/GraphicNode.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <stdexcept>
#include <variant>

namespace {

using testing::Eq;

using composite_pattern_modern::Group;
using composite_pattern_modern::Node;
using composite_pattern_modern::area;
using composite_pattern_modern::group;
using composite_pattern_modern::render;
using composite_pattern_modern::shape;

TEST(CompositeModern, ShapeNodeCarriesLeafData)
{
    const Node circle = shape("Circle", 12.0);

    EXPECT_THAT(area(circle), Eq(12.0));

    std::ostringstream output;
    render(circle, output);

    EXPECT_THAT(output.str(), Eq("- Circle (12)\n"));
}

TEST(CompositeModern, GroupAggregatesChildAreas)
{
    const Node scene = group("Scene", {shape("Rectangle", 20.0), shape("Triangle", 15.0)});

    EXPECT_THAT(area(scene), Eq(35.0));

    const auto& group_ptr = std::get<std::shared_ptr<Group>>(scene);
    EXPECT_THAT(group_ptr->child_count(), Eq(2U));
}

TEST(CompositeModern, NestedGroupsRenderAsOneTree)
{
    const Node screen = group(
        "Screen",
        {
            shape("Canvas", 40.0),
            group("Toolbar", {shape("Save", 2.0), shape("Open", 3.0)}),
        });

    std::ostringstream output;
    render(screen, output);

    EXPECT_THAT(area(screen), Eq(45.0));
    EXPECT_THAT(output.str(),
                Eq("+ Screen (45)\n"
                   "  - Canvas (40)\n"
                   "  + Toolbar (5)\n"
                   "    - Save (2)\n"
                   "    - Open (3)\n"));
}

TEST(CompositeModern, GroupsCanBeBuiltIncrementally)
{
    auto root = std::make_shared<Group>("Root");
    root->add(shape("Circle", 10.0));
    root->add(group("Nested", {shape("Triangle", 5.0)}));

    const Node node = root;

    EXPECT_THAT(root->child_count(), Eq(2U));
    EXPECT_THAT(area(node), Eq(15.0));
}

TEST(CompositeModern, RejectsInvalidNodes)
{
    EXPECT_THROW(
        {
            [[maybe_unused]] const auto invalid_shape = shape("", 1.0);
        },
        std::invalid_argument);
    EXPECT_THROW(
        {
            [[maybe_unused]] const auto invalid_shape = shape("Broken", -1.0);
        },
        std::invalid_argument);
    EXPECT_THROW(
        {
            [[maybe_unused]] const auto invalid_group = group("");
        },
        std::invalid_argument);

    const Node null_group = std::shared_ptr<Group>{};
    EXPECT_THROW(
        {
            [[maybe_unused]] const auto total = area(null_group);
        },
        std::invalid_argument);
}

}  // namespace
