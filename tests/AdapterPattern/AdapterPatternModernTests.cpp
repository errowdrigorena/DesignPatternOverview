#include <AdapterPattern_common/LegacyThermometerCApi.h>
#include <AdapterPattern_modern/SensorAdapters.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using testing::Eq;

using adapter_pattern_modern::ThermometerSensor;

TEST(ModernAdapter, ObjectAdaptsTheCApiToARegularCxxObject)
{
    ThermometerSensor sensor{"tank-1", 12.0};

    sensor.calibrate(-0.75);

    EXPECT_THAT(sensor.id(), Eq("tank-1"));
    EXPECT_DOUBLE_EQ(sensor.read_celsius(), 11.25);
}

TEST(ModernAdapter, ObjectOwnsTheAdaptedCResourceAndReleasesItOnDestruction)
{
    EXPECT_EQ(legacy_thermometer_active_handles(), 0);

    {
        ThermometerSensor sensor{"tank-1", 12.0};
        EXPECT_EQ(legacy_thermometer_active_handles(), 1);
    }

    EXPECT_EQ(legacy_thermometer_active_handles(), 0);
}

}  // namespace
