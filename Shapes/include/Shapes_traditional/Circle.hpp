#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <memory>

namespace shapes_traditional {

class Circle final : public Shape {
public:
    explicit Circle(double radius);

    [[nodiscard]] static std::unique_ptr<Shape> create(double radius);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double radius_;
};

}  // namespace shapes_traditional
