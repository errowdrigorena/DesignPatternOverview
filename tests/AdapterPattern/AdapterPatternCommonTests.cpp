#include <AdapterPattern_common/LegacyThermometerCApi.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

namespace {

using testing::Eq;
using testing::Ne;

TEST(AdapterPatternCommon, LegacyCApiUsesStructsAndFreeFunctions)
{
    legacy_thermometer_handle* thermometer = legacy_thermometer_create("boiler-1", 21.5);

    ASSERT_THAT(thermometer, Ne(nullptr));
    EXPECT_THAT(legacy_thermometer_id(thermometer), Eq(std::string{"boiler-1"}));
    EXPECT_DOUBLE_EQ(legacy_thermometer_read_celsius(thermometer), 21.5);

    legacy_thermometer_calibrate(thermometer, 1.25);

    EXPECT_DOUBLE_EQ(legacy_thermometer_read_celsius(thermometer), 22.75);

    legacy_thermometer_destroy(thermometer);
}

TEST(AdapterPatternCommon, LegacyCApiReportsActiveHandles)
{
    EXPECT_EQ(legacy_thermometer_active_handles(), 0);

    legacy_thermometer_handle* thermometer = legacy_thermometer_create("oven-1", 180.0);

    ASSERT_THAT(thermometer, Ne(nullptr));
    EXPECT_EQ(legacy_thermometer_active_handles(), 1);

    legacy_thermometer_destroy(thermometer);

    EXPECT_EQ(legacy_thermometer_active_handles(), 0);
}

}  // namespace
