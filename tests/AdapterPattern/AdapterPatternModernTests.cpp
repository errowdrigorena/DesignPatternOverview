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

TEST(ModernAdapter, ObjectOwnsTheAdaptedCResource)
{
    ThermometerSensor sensor{"tank-1", 12.0};

    EXPECT_THAT(sensor.id(), Eq("tank-1"));
    EXPECT_DOUBLE_EQ(sensor.read_celsius(), 12.0);
}

}  // namespace
