#pragma once

namespace shapes_modern {

class Circle {
public:
    explicit Circle(double radius);

    void draw() const;
    [[nodiscard]] double calculate_area() const;

private:
    double radius_;
};

}  // namespace shapes_modern
