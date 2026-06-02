#pragma once

#include <VisitorPattern_classic/Shape.hpp>

namespace visitor_pattern_classic {

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height);

    [[nodiscard]] double width() const;
    [[nodiscard]] double height() const;

    void accept(ShapeVisitor& visitor) const override;

private:
    double width_;
    double height_;
};

}  // namespace visitor_pattern_classic
