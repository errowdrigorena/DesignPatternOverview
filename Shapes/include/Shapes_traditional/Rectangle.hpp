#pragma once

#include <Shapes_traditional/Shapes.hpp>

namespace shapes_traditional {

class Rectangle final : public Shapes {
public:
    Rectangle(double width, double height);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double width_;
    double height_;
};

}  // namespace shapes_traditional
