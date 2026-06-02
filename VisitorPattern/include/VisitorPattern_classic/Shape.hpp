#pragma once

namespace visitor_pattern_classic {

class ShapeVisitor;

class Shape {
public:
    virtual ~Shape() = default;

    virtual void accept(ShapeVisitor& visitor) const = 0;
};

}  // namespace visitor_pattern_classic
