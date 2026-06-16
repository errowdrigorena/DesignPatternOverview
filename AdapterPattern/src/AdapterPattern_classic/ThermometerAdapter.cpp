#include <AdapterPattern_classic/ThermometerAdapter.hpp>

#include <AdapterPattern_common/LegacyThermometerCApi.h>

#include <memory>

namespace adapter_pattern_classic {

struct ThermometerAdapter::Impl {
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

ThermometerAdapter::ThermometerAdapter(std::string id, double initial_celsius)
    : impl_{std::make_unique<Impl>(id, initial_celsius)}
{
}

ThermometerAdapter::~ThermometerAdapter() = default;

ThermometerAdapter::ThermometerAdapter(ThermometerAdapter&&) noexcept = default;

ThermometerAdapter& ThermometerAdapter::operator=(ThermometerAdapter&&) noexcept = default;

double ThermometerAdapter::read_celsius() const
{
    return legacy_thermometer_read_celsius(impl_->handle);
}

void ThermometerAdapter::calibrate(double offset)
{
    legacy_thermometer_calibrate(impl_->handle, offset);
}

std::string ThermometerAdapter::id() const
{
    return legacy_thermometer_id(impl_->handle);
}

}  // namespace adapter_pattern_classic
