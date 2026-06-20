#include <BuilderPattern_classic/ConcreteRectangleBuilder.hpp>
#include <BuilderPattern_classic/RectangleDirector.hpp>

#include <gtest/gtest.h>

#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

class RecordingRectangleBuilder final : public builder_pattern_classic::RectangleBuilder {
public:
    void reset() override
    {
        steps.push_back("reset");
    }

    void set_name(const std::string_view name) override
    {
        steps.push_back("name=" + std::string{name});
    }

    void set_width(const double width) override
    {
        steps.push_back("width=" + std::to_string(width));
    }

    void set_height(const double height) override
    {
        steps.push_back("height=" + std::to_string(height));
    }

    std::vector<std::string> steps;
};

TEST(BuilderClassic, BuildsRectangleFromItsThreeRequiredValues)
{
    builder_pattern_classic::ConcreteRectangleBuilder builder;
    const builder_pattern_classic::RectangleDirector director;
    director.construct(builder, "selection-box", 120.0, 80.0);

    const auto rectangle = builder.build();

    EXPECT_EQ(rectangle.name(), "selection-box");
    EXPECT_EQ(rectangle.width(), 120.0);
    EXPECT_EQ(rectangle.height(), 80.0);
    EXPECT_EQ(rectangle.area(), 9600.0);
}

TEST(BuilderClassic, RejectsMissingOrInvalidValues)
{
    builder_pattern_classic::ConcreteRectangleBuilder builder;

    EXPECT_THROW(static_cast<void>(builder.build()), std::logic_error);

    builder.set_name("selection-box");
    builder.set_width(-1.0);
    builder.set_height(80.0);
    EXPECT_THROW(static_cast<void>(builder.build()), std::logic_error);

    builder.set_width(120.0);
    builder.set_height(std::numeric_limits<double>::infinity());
    EXPECT_THROW(static_cast<void>(builder.build()), std::logic_error);
}

TEST(BuilderClassic, DirectorResetsTheConcreteBuilder)
{
    builder_pattern_classic::ConcreteRectangleBuilder builder;
    const builder_pattern_classic::RectangleDirector director;

    builder.set_name("stale");
    builder.set_width(1.0);
    builder.set_height(1.0);

    director.construct(builder, "selection-box", 120.0, 80.0);
    const auto rectangle = builder.build();

    EXPECT_EQ(rectangle.name(), "selection-box");
    EXPECT_EQ(rectangle.area(), 9600.0);
}

TEST(BuilderClassic, DirectorUsesTheAbstractBuilderProtocol)
{
    RecordingRectangleBuilder builder;
    const builder_pattern_classic::RectangleDirector director;

    director.construct(builder, "selection-box", 120.0, 80.0);

    EXPECT_EQ(
        builder.steps,
        (std::vector<std::string>{
            "reset",
            "name=selection-box",
            "width=120",
            "height=80",
        }));
}

}  // namespace
