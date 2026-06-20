#pragma once

#include <string>
#include <string_view>

namespace builder_pattern_classic {
class ConcreteRectangleBuilder;
}

namespace builder_pattern_modern {
class RectangleBuilder;
}

namespace builder_pattern_common {

class Rectangle {
public:
    [[nodiscard]] std::string_view name() const;
    [[nodiscard]] double width() const;
    [[nodiscard]] double height() const;
    [[nodiscard]] double area() const;

private:
    Rectangle(std::string name, double width, double height);

    friend class ::builder_pattern_classic::ConcreteRectangleBuilder;
    friend class ::builder_pattern_modern::RectangleBuilder;

    std::string name_;
    double width_;
    double height_;
};

}  // namespace builder_pattern_common
