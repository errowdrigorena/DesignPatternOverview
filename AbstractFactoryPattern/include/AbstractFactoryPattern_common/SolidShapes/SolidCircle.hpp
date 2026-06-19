#pragma once

#include <AbstractFactoryPattern_common/StyledShape.hpp>

namespace abstract_factory_pattern_common {

class SolidCircle final : public StyledShape {
public:
    explicit SolidCircle(double radius);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;
    [[nodiscard]] std::string_view family() const override;

private:
    double radius_;
};

}  // namespace abstract_factory_pattern_common
