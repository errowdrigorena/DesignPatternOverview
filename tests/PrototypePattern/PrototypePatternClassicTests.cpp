#include <PrototypePattern_classic/Prototype.h>

#include <gtest/gtest.h>

#include <memory>
#include <sstream>

namespace {

using prototype_pattern_classic::UiCardPrototype;

std::string describe(const UiCardPrototype& prototype)
{
    std::ostringstream output;
    prototype.draw(output);
    return output.str();
}

TEST(ClassicPrototype, DrawsCardWithoutLayers)
{
    const UiCardPrototype prototype{"summary", 1.25};

    EXPECT_EQ(describe(prototype), "UiCardPrototype{name=summary, scale=1.25, layers=[]}\n");
}

TEST(ClassicPrototype, DrawsCardWithLayers)
{
    UiCardPrototype prototype{"dashboard", 2.0};

    prototype.add_layer("background");
    prototype.add_layer("content");
    prototype.add_layer("actions");

    EXPECT_EQ(
        describe(prototype),
        "UiCardPrototype{name=dashboard, scale=2, layers=[background, content, actions]}\n");
}

TEST(ClassicPrototype, CloneCopiesCurrentState)
{
    UiCardPrototype original{"profile", 1.5};
    original.add_layer("avatar");
    original.add_layer("metadata");

    const std::unique_ptr<UiCardPrototype> clone{original.clone()};

    EXPECT_EQ(describe(*clone), "UiCardPrototype{name=profile, scale=1.5, layers=[avatar, metadata]}\n");
}

TEST(ClassicPrototype, MutatingCloneDoesNotChangeOriginal)
{
    UiCardPrototype original{"profile", 1.5};
    original.add_layer("avatar");
    const std::unique_ptr<UiCardPrototype> clone{original.clone()};

    clone->set_name("compact-profile");
    clone->set_scale(0.75);
    clone->add_layer("badge");

    EXPECT_EQ(describe(original), "UiCardPrototype{name=profile, scale=1.5, layers=[avatar]}\n");
    EXPECT_EQ(describe(*clone), "UiCardPrototype{name=compact-profile, scale=0.75, layers=[avatar, badge]}\n");
}

}  // namespace
