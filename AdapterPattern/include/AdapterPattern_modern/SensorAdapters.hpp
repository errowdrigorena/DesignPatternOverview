#pragma once

#include <memory>
#include <string>
#include <utility>

namespace adapter_pattern_modern {

class Sensor {
public:
    Sensor(std::string id, double temperature)
        : id_{std::move(id)}
        , temperature_{temperature}
    {
    }

    [[nodiscard]] std::string id() const
    {
        return id_;
    }

    [[nodiscard]] double read_celsius() const
    {
        return temperature_;
    }

    void calibrate(double offset)
    {
        temperature_ += offset;
    }

private:
    std::string id_;
    double temperature_{};
};

inline Sensor make_fixed_sensor(std::string id, double temperature)
{
    return Sensor{std::move(id), temperature};
}

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
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

inline ThermometerSensor make_thermometer_sensor(std::string id, double initial_celsius)
{
    return ThermometerSensor{std::move(id), initial_celsius};
}

}  // namespace adapter_pattern_modern
