#pragma once

#include <functional>

namespace shapes_strategy_function {

class Rectangle final {
public:
    using DrawStrategy = std::function<void(Rectangle const&)>;

    Rectangle(double width, double height, DrawStrategy draw_strategy);

    void draw() const;
    [[nodiscard]] double calculate_area() const;
    void set_strategy(DrawStrategy draw_strategy);

    [[nodiscard]] double width() const;
    [[nodiscard]] double height() const;

private:
    double width_;
    double height_;
    DrawStrategy draw_strategy_;
};

}  // namespace shapes_strategy_function
