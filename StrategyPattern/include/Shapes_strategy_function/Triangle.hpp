#pragma once

#include <functional>

namespace shapes_strategy_function {

class Triangle final {
public:
    using DrawStrategy = std::function<void(Triangle const&)>;

    Triangle(double base, double height, DrawStrategy draw_strategy);

    void draw() const;
    [[nodiscard]] double calculate_area() const;
    void set_strategy(DrawStrategy draw_strategy);

    [[nodiscard]] double base() const;
    [[nodiscard]] double height() const;

private:
    double base_;
    double height_;
    DrawStrategy draw_strategy_;
};

}  // namespace shapes_strategy_function
