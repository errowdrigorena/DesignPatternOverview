#include <AdapterPattern_classic/TemperatureSensor.hpp>
#include <AdapterPattern_classic/ThermometerAdapter.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

namespace {

using testing::Eq;

using adapter_pattern_classic::TemperatureSensor;
using adapter_pattern_classic::ThermometerAdapter;

TEST(ClassicAdapter, AdapterExposesTheLegacyHandleAsAnObject)
{
    ThermometerAdapter sensor{"boiler-1", 21.5};

    EXPECT_THAT(sensor.id(), Eq("boiler-1"));
    EXPECT_DOUBLE_EQ(sensor.read_celsius(), 21.5);

    sensor.calibrate(1.25);

    EXPECT_DOUBLE_EQ(sensor.read_celsius(), 22.75);
}

TEST(ClassicAdapter, AdapterCanBeUsedThroughTheTargetInterface)
{
    std::unique_ptr<TemperatureSensor> sensor =
        std::make_unique<ThermometerAdapter>("freezer-1", -18.0);

    sensor->calibrate(-0.5);

    EXPECT_THAT(sensor->id(), Eq("freezer-1"));
    EXPECT_DOUBLE_EQ(sensor->read_celsius(), -18.5);
}

}  // namespace
