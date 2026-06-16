#pragma once

#include <AdapterPattern_classic/TemperatureSensor.hpp>
#include <AdapterPattern_common/LegacyThermometerCApi.h>

#include <memory>

namespace adapter_pattern_classic {

class ThermometerAdapter final : public TemperatureSensor {
public:
    ThermometerAdapter(std::string id, double initial_celsius);
    ~ThermometerAdapter() override;

    ThermometerAdapter(const ThermometerAdapter&) = delete;
    ThermometerAdapter& operator=(const ThermometerAdapter&) = delete;
    ThermometerAdapter(ThermometerAdapter&&) noexcept;
    ThermometerAdapter& operator=(ThermometerAdapter&&) noexcept;

    [[nodiscard]] double read_celsius() const override;
    void calibrate(double offset) override;
    [[nodiscard]] std::string id() const override;

private:
    struct LegacyThermometerDeleter {
        void operator()(legacy_thermometer_handle* handle) const;
    };

    std::unique_ptr<legacy_thermometer_handle, LegacyThermometerDeleter> handle_;
};

}  // namespace adapter_pattern_classic
