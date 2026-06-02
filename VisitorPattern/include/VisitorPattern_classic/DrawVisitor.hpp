#pragma once

#include <VisitorPattern_classic/ShapeVisitor.hpp>

#include <iosfwd>

namespace visitor_pattern_classic {

class DrawVisitor final : public ShapeVisitor {
public:
    explicit DrawVisitor(std::ostream& output);

    void visit(const Circle& circle) override;
    void visit(const Rectangle& rectangle) override;
    void visit(const Triangle& triangle) override;

private:
    std::ostream& output_;
};

}  // namespace visitor_pattern_classic
