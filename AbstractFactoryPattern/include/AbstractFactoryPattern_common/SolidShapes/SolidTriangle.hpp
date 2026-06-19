#pragma once

#include <AbstractFactoryPattern_common/StyledShape.hpp>

namespace abstract_factory_pattern_common {

class SolidTriangle final : public StyledShape {
public:
    SolidTriangle(double base, double height);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;
    [[nodiscard]] std::string_view family() const override;

private:
    double base_;
    double height_;
};

}  // namespace abstract_factory_pattern_common
