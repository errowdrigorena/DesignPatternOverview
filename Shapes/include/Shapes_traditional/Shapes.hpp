#pragma once

namespace shapes_traditional {

class Shapes {
public:
    virtual ~Shapes() = default;

    virtual void draw() const = 0;
    [[nodiscard]] virtual double calculate_area() const = 0;
};

}  // namespace shapes_traditional
