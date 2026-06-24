#pragma once

#include <Shapes_strategy_classic/Shape.hpp>

#include <memory>

namespace shapes_strategy {

class Triangle_strategy final : public Shape {
public:
    Triangle_strategy(double base, double height, std::unique_ptr<DrawStrategy> draw_strategy);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double base_;
    double height_;
};

}  // namespace shapes_strategy
