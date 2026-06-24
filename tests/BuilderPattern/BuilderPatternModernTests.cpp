#include <BuilderPattern_modern/RectangleBuilder.hpp>

#include <gtest/gtest.h>

#include <stdexcept>

namespace {

TEST(BuilderModern, BuildsRectangleWithAFluentApi)
{
    const auto rectangle = builder_pattern_modern::RectangleBuilder{}
                               .name("selection-box")
                               .width(120.0)
                               .height(80.0)
                               .build();

    EXPECT_EQ(rectangle.name(), "selection-box");
    EXPECT_EQ(rectangle.width(), 120.0);
    EXPECT_EQ(rectangle.height(), 80.0);
    EXPECT_EQ(rectangle.area(), 9600.0);
}

TEST(BuilderModern, RejectsAnIncompleteRectangle)
{
    EXPECT_THROW(
        static_cast<void>(
            builder_pattern_modern::RectangleBuilder{}
                .name("selection-box")
                .width(120.0)
                .build()),
        std::logic_error);
}

TEST(BuilderModern, EachFreshBuilderProducesAnIndependentConfiguration)
{
    const auto thumbnail = builder_pattern_modern::RectangleBuilder{}
                               .name("thumbnail")
                               .width(16.0)
                               .height(9.0)
                               .build();

    const auto banner = builder_pattern_modern::RectangleBuilder{}
                            .name("banner")
                            .width(1920.0)
                            .height(1080.0)
                            .build();

    EXPECT_EQ(thumbnail.name(), "thumbnail");
    EXPECT_DOUBLE_EQ(thumbnail.width(), 16.0);
    EXPECT_DOUBLE_EQ(thumbnail.height(), 9.0);
    EXPECT_DOUBLE_EQ(thumbnail.area(), 144.0);

    EXPECT_EQ(banner.name(), "banner");
    EXPECT_DOUBLE_EQ(banner.width(), 1920.0);
    EXPECT_DOUBLE_EQ(banner.height(), 1080.0);
    EXPECT_DOUBLE_EQ(banner.area(), 2073600.0);
}

}  // namespace
