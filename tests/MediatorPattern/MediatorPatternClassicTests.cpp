#include <MediatorPattern_classic/RectangleDialog.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

namespace {

TEST(MediatorClassic, FieldsDoNotChangeEachOtherWithoutTheCoordinationRule)
{
    std::ostringstream output;
    mediator_pattern_classic::RectangleDialog dialog{4.0, 2.0, output};

    dialog.width_field().enter_value(6.0);

    EXPECT_DOUBLE_EQ(dialog.width_field().value(), 6.0);
    EXPECT_DOUBLE_EQ(dialog.height_field().value(), 2.0);
    EXPECT_EQ(output.str(), "Preview: 6 x 2\n");
}

TEST(MediatorClassic, MediatorAppliesAspectRatioWhenTheCheckBoxIsEnabled)
{
    std::ostringstream output;
    mediator_pattern_classic::RectangleDialog dialog{4.0, 2.0, output};

    dialog.keep_aspect_ratio_check_box().toggle();
    dialog.width_field().enter_value(12.0);

    EXPECT_DOUBLE_EQ(dialog.width_field().value(), 12.0);
    EXPECT_DOUBLE_EQ(dialog.height_field().value(), 6.0);
    EXPECT_EQ(output.str(), "Preview: 4 x 2\nPreview: 12 x 6\n");
}

TEST(MediatorClassic, MediatorCoordinatesTheOtherDirectionToo)
{
    std::ostringstream output;
    mediator_pattern_classic::RectangleDialog dialog{4.0, 2.0, output};

    dialog.keep_aspect_ratio_check_box().toggle();
    dialog.height_field().enter_value(5.0);

    EXPECT_DOUBLE_EQ(dialog.width_field().value(), 10.0);
    EXPECT_DOUBLE_EQ(dialog.height_field().value(), 5.0);
    EXPECT_DOUBLE_EQ(dialog.preview().displayed_width(), 10.0);
    EXPECT_DOUBLE_EQ(dialog.preview().displayed_height(), 5.0);
}

TEST(MediatorClassic, ProgrammaticUpdatesDoNotStartAnotherNotificationCycle)
{
    std::ostringstream output;
    mediator_pattern_classic::RectangleDialog dialog{4.0, 2.0, output};

    dialog.keep_aspect_ratio_check_box().toggle();
    dialog.width_field().enter_value(12.0);

    EXPECT_EQ(dialog.preview().update_count(), 2U);
}

TEST(MediatorClassic, RectangleDimensionsMustBePositive)
{
    std::ostringstream output;

    EXPECT_THROW((mediator_pattern_classic::RectangleDialog{0.0, 2.0, output}), std::invalid_argument);
    EXPECT_THROW((mediator_pattern_classic::RectangleDialog{4.0, -1.0, output}), std::invalid_argument);
}

TEST(MediatorClassic, UserCannotEnterANonPositiveDimension)
{
    std::ostringstream output;
    mediator_pattern_classic::RectangleDialog dialog{4.0, 2.0, output};

    EXPECT_THROW(dialog.width_field().enter_value(0.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(dialog.width_field().value(), 4.0);
    EXPECT_TRUE(output.str().empty());
}

}  // namespace
