#include <AdapterPattern_modern/SensorAdapters.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

namespace {

using testing::Eq;

using adapter_pattern_modern::make_fixed_sensor;
using adapter_pattern_modern::make_thermometer_sensor;

TEST(ModernAdapter, FactoryAdaptsTheCApiToARegularCxxObject)
{
    auto sensor = make_thermometer_sensor("tank-1", 12.0);

    sensor.calibrate(-0.75);

    EXPECT_THAT(sensor.id(), Eq("tank-1"));
    EXPECT_DOUBLE_EQ(sensor.read_celsius(), 11.25);
}

TEST(ModernAdapter, NativeAndAdaptedSensorsShareTheSameSurface)
{
    auto native_sensor = make_fixed_sensor("room-1", 19.5);
    auto adapted_sensor = make_thermometer_sensor("tank-1", 12.0);

    EXPECT_THAT(native_sensor.id(), Eq("room-1"));
    EXPECT_DOUBLE_EQ(native_sensor.read_celsius(), 19.5);
    EXPECT_THAT(adapted_sensor.id(), Eq("tank-1"));
    EXPECT_DOUBLE_EQ(adapted_sensor.read_celsius(), 12.0);
}

}  // namespace
