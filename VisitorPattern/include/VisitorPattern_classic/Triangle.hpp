#pragma once

#include <VisitorPattern_classic/Shape.hpp>

namespace visitor_pattern_classic {

class Triangle final : public Shape {
public:
    Triangle(double base, double height);

    [[nodiscard]] double base() const;
    [[nodiscard]] double height() const;

    void accept(ShapeVisitor& visitor) const override;

private:
    double base_;
    double height_;
};

}  // namespace visitor_pattern_classic
