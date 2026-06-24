#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <memory>

namespace shapes_traditional {

class Triangle final : public Shape {
public:
    Triangle(double base, double height);

    [[nodiscard]] static std::unique_ptr<Shape> create(double base, double height);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double base_;
    double height_;
};

}  // namespace shapes_traditional
