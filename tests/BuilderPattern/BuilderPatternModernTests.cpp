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

}  // namespace
