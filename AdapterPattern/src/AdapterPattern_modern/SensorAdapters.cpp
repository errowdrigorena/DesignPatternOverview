#include <AdapterPattern_modern/SensorAdapters.hpp>

namespace adapter_pattern_modern {

ThermometerSensor::ThermometerSensor(std::string id, double initial_celsius)
    : handle_{legacy_thermometer_create(id.c_str(), initial_celsius)}
{
}

ThermometerSensor::~ThermometerSensor() = default;

ThermometerSensor::ThermometerSensor(ThermometerSensor&&) noexcept = default;

ThermometerSensor& ThermometerSensor::operator=(ThermometerSensor&&) noexcept = default;

std::string ThermometerSensor::id() const
{
    return legacy_thermometer_id(handle_.get());
}

double ThermometerSensor::read_celsius() const
{
    return legacy_thermometer_read_celsius(handle_.get());
}

void ThermometerSensor::calibrate(double offset)
{
    legacy_thermometer_calibrate(handle_.get(), offset);
}

void ThermometerSensor::LegacyThermometerDeleter::operator()(legacy_thermometer_handle* handle) const
{
    legacy_thermometer_destroy(handle);
}

}  // namespace adapter_pattern_modern
