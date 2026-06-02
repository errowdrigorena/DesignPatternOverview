#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <memory>

namespace shapes_traditional {

class Circle final : public Shapes {
public:
    explicit Circle(double radius);

    [[nodiscard]] static std::unique_ptr<Shapes> create(double radius);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double radius_;
};

}  // namespace shapes_traditional
