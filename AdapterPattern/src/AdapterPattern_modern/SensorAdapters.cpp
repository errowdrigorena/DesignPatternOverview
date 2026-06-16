#include <AdapterPattern_modern/SensorAdapters.hpp>

#include <AdapterPattern_common/LegacyThermometerCApi.h>

#include <memory>

namespace adapter_pattern_modern {

struct ThermometerSensor::Impl {
    Impl(const std::string& id, double initial_celsius)
        : handle{legacy_thermometer_create(id.c_str(), initial_celsius)}
    {
    }

    ~Impl()
    {
        legacy_thermometer_destroy(handle);
    }

    legacy_thermometer_handle* handle{};
};

ThermometerSensor::ThermometerSensor(std::string id, double initial_celsius)
    : impl_{std::make_unique<Impl>(id, initial_celsius)}
{
}

ThermometerSensor::~ThermometerSensor() = default;

ThermometerSensor::ThermometerSensor(ThermometerSensor&&) noexcept = default;

ThermometerSensor& ThermometerSensor::operator=(ThermometerSensor&&) noexcept = default;

std::string ThermometerSensor::id() const
{
    return legacy_thermometer_id(impl_->handle);
}

double ThermometerSensor::read_celsius() const
{
    return legacy_thermometer_read_celsius(impl_->handle);
}

void ThermometerSensor::calibrate(double offset)
{
    legacy_thermometer_calibrate(impl_->handle, offset);
}

}  // namespace adapter_pattern_modern
