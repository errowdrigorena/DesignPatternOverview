#pragma once

#include <AbstractFactoryPattern_common/StyledShape.hpp>

namespace abstract_factory_pattern_common {

class SolidRectangle final : public StyledShape {
public:
    SolidRectangle(double width, double height);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;
    [[nodiscard]] std::string_view family() const override;

private:
    double width_;
    double height_;
};

}  // namespace abstract_factory_pattern_common
