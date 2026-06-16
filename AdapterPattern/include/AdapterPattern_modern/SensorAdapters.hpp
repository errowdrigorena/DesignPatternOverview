#pragma once

#include <AdapterPattern_common/LegacyThermometerCApi.h>

#include <memory>
#include <string>

namespace adapter_pattern_modern {

class ThermometerSensor {
public:
    ThermometerSensor(std::string id, double initial_celsius);
    ~ThermometerSensor();

    ThermometerSensor(const ThermometerSensor&) = delete;
    ThermometerSensor& operator=(const ThermometerSensor&) = delete;
    ThermometerSensor(ThermometerSensor&&) noexcept;
    ThermometerSensor& operator=(ThermometerSensor&&) noexcept;

    [[nodiscard]] std::string id() const;
    [[nodiscard]] double read_celsius() const;
    void calibrate(double offset);

private:
    struct LegacyThermometerDeleter {
        void operator()(legacy_thermometer_handle* handle) const;
    };

    std::unique_ptr<legacy_thermometer_handle, LegacyThermometerDeleter> handle_;
};

}  // namespace adapter_pattern_modern
