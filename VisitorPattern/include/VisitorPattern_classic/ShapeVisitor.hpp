#pragma once

namespace visitor_pattern_classic {

class Circle;
class Rectangle;
class Triangle;

class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;

    virtual void visit(const Circle& circle) = 0;
    virtual void visit(const Rectangle& rectangle) = 0;
    virtual void visit(const Triangle& triangle) = 0;
};

}  // namespace visitor_pattern_classic
