#pragma once

#include <Shapes_strategy/Shapes.hpp>

#include <memory>

namespace shapes_strategy {

class Circle_strategy final : public Shapes {
public:
    Circle_strategy(double radius, std::unique_ptr<DrawStrategy> draw_strategy);

    void draw() const override;
    [[nodiscard]] double calculate_area() const override;

private:
    double radius_;
};

}  // namespace shapes_strategy
