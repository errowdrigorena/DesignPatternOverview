#pragma once

#include <functional>

namespace shapes_strategy_function {

class Circle final {
public:
    using DrawStrategy = std::function<void(Circle const&)>;

    Circle(double radius, DrawStrategy draw_strategy);

    void draw() const;
    [[nodiscard]] double calculate_area() const;
    void set_strategy(DrawStrategy draw_strategy);

    [[nodiscard]] double radius() const;

private:
    double radius_;
    DrawStrategy draw_strategy_;
};

}  // namespace shapes_strategy_function
