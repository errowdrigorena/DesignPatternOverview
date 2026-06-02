#pragma once

#include <VisitorPattern_classic/ShapeVisitor.hpp>

namespace visitor_pattern_classic {

class AreaVisitor final : public ShapeVisitor {
public:
    void visit(const Circle& circle) override;
    void visit(const Rectangle& rectangle) override;
    void visit(const Triangle& triangle) override;

    [[nodiscard]] double area() const;

private:
    double area_{0.0};
};

}  // namespace visitor_pattern_classic
