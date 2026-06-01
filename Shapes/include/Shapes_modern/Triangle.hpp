#pragma once

namespace shapes_modern {

class Triangle {
public:
    Triangle(double base, double height);

    void draw() const;
    [[nodiscard]] double calculate_area() const;

private:
    double base_;
    double height_;
};

}  // namespace shapes_modern
