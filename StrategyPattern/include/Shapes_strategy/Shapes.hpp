#pragma once

#include <Shapes_strategy/DrawStrategy.hpp>

#include <memory>

namespace shapes_strategy {

class Shapes {
public:
    explicit Shapes(std::unique_ptr<DrawStrategy> draw_strategy);
    virtual ~Shapes() = default;

    virtual void draw() const = 0;
    [[nodiscard]] virtual double calculate_area() const = 0;

    void set_strategy(std::unique_ptr<DrawStrategy> draw_strategy);

protected:
    std::unique_ptr<DrawStrategy> draw_strategy_;
};

}  // namespace shapes_strategy
