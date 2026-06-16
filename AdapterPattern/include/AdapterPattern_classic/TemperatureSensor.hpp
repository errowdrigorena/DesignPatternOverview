#pragma once

#include <string>

namespace adapter_pattern_classic {

class TemperatureSensor {
public:
    virtual ~TemperatureSensor() = default;

    [[nodiscard]] virtual double read_celsius() const = 0;
    virtual void calibrate(double offset) = 0;
    [[nodiscard]] virtual std::string id() const = 0;
};

}  // namespace adapter_pattern_classic
