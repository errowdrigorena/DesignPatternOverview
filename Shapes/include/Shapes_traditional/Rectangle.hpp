#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <memory>

namespace shapes_traditional {

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height);

    [[nodiscard]] static std::unique_ptr<Shape> create(double width, double height);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double width_;
    double height_;
};

}  // namespace shapes_traditional
