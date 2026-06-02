#pragma once

#include <VisitorPattern_classic/Shape.hpp>

namespace visitor_pattern_classic {

class Circle final : public Shape {
public:
    explicit Circle(double radius);

    [[nodiscard]] double radius() const;

    void accept(ShapeVisitor& visitor) const override;

private:
    double radius_;
};

}  // namespace visitor_pattern_classic
