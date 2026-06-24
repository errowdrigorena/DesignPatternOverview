#pragma once

#include <Shapes_strategy_classic/Shape.hpp>

#include <memory>

namespace shapes_strategy {

class Rectangle_strategy final : public Shape {
public:
    Rectangle_strategy(double width, double height, std::unique_ptr<DrawStrategy> draw_strategy);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double width_;
    double height_;
};

}  // namespace shapes_strategy
