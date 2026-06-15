#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <memory>

namespace shapes_traditional {

class Triangle final : public Shapes {
public:
    Triangle(double base, double height);

    [[nodiscard]] static std::unique_ptr<Shapes> create(double base, double height);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double base_;
    double height_;
};

}  // namespace shapes_traditional
