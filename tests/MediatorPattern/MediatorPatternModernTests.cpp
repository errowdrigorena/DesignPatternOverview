#include <MediatorPattern_modern/RectangleDialog.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace {

TEST(MediatorModern, FieldsDoNotChangeEachOtherWithoutTheCoordinationRule)
{
    std::ostringstream output;
    mediator_pattern_modern::RectangleDialog dialog{4.0, 2.0, output};

    dialog.width_field().enter_value(6.0);

    EXPECT_DOUBLE_EQ(dialog.width_field().value(), 6.0);
    EXPECT_DOUBLE_EQ(dialog.height_field().value(), 2.0);
    EXPECT_EQ(output.str(), "Preview: 6 x 2\n");
}

TEST(MediatorModern, CallbacksStillCentralizeTheAspectRatioRule)
{
    std::ostringstream output;
    mediator_pattern_modern::RectangleDialog dialog{4.0, 2.0, output};

    dialog.keep_aspect_ratio_check_box().toggle();
    dialog.width_field().enter_value(12.0);

    EXPECT_DOUBLE_EQ(dialog.width_field().value(), 12.0);
    EXPECT_DOUBLE_EQ(dialog.height_field().value(), 6.0);
    EXPECT_EQ(output.str(), "Preview: 4 x 2\nPreview: 12 x 6\n");
}

TEST(MediatorModern, CallbacksCoordinateChangesFromEitherField)
{
    std::ostringstream output;
    mediator_pattern_modern::RectangleDialog dialog{4.0, 2.0, output};

    dialog.keep_aspect_ratio_check_box().toggle();
    dialog.height_field().enter_value(5.0);

    EXPECT_DOUBLE_EQ(dialog.width_field().value(), 10.0);
    EXPECT_DOUBLE_EQ(dialog.height_field().value(), 5.0);
    EXPECT_DOUBLE_EQ(dialog.preview().displayed_width(), 10.0);
    EXPECT_DOUBLE_EQ(dialog.preview().displayed_height(), 5.0);
}

TEST(MediatorModern, ProgrammaticUpdatesDoNotTriggerTheCallbacksAgain)
{
    std::ostringstream output;
    mediator_pattern_modern::RectangleDialog dialog{4.0, 2.0, output};

    dialog.keep_aspect_ratio_check_box().toggle();
    dialog.width_field().enter_value(12.0);

    EXPECT_EQ(dialog.preview().update_count(), 2U);
}

}  // namespace
