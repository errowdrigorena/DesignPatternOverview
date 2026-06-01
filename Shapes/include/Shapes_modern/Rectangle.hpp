#pragma once

namespace shapes_modern {

class Rectangle {
public:
    Rectangle(double width, double height);

    void draw() const;
    [[nodiscard]] double calculate_area() const;

private:
    double width_;
    double height_;
};

}  // namespace shapes_modern
