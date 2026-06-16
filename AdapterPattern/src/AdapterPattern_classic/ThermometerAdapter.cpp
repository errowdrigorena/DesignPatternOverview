#include <AdapterPattern_classic/ThermometerAdapter.hpp>

namespace adapter_pattern_classic {

ThermometerAdapter::ThermometerAdapter(std::string id, double initial_celsius)
    : handle_{legacy_thermometer_create(id.c_str(), initial_celsius)}
{
}

ThermometerAdapter::~ThermometerAdapter() = default;

ThermometerAdapter::ThermometerAdapter(ThermometerAdapter&&) noexcept = default;

ThermometerAdapter& ThermometerAdapter::operator=(ThermometerAdapter&&) noexcept = default;

double ThermometerAdapter::read_celsius() const
{
    return legacy_thermometer_read_celsius(handle_.get());
}

void ThermometerAdapter::calibrate(double offset)
{
    legacy_thermometer_calibrate(handle_.get(), offset);
}

std::string ThermometerAdapter::id() const
{
    return legacy_thermometer_id(handle_.get());
}

void ThermometerAdapter::LegacyThermometerDeleter::operator()(legacy_thermometer_handle* handle) const
{
    legacy_thermometer_destroy(handle);
}

}  // namespace adapter_pattern_classic
