#pragma once

#include <variant>

namespace visitor_pattern_modern {

struct Circle {
    double radius;
};

struct Rectangle {
    double width;
    double height;
};

struct Triangle {
    double base;
    double height;
};

using Shape = std::variant<Circle, Rectangle, Triangle>;

}  // namespace visitor_pattern_modern
