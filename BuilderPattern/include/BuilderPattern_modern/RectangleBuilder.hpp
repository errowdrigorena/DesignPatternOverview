#pragma once

#include <BuilderPattern_common/Rectangle.hpp>

#include <optional>
#include <string>
#include <string_view>

namespace builder_pattern_modern {

class RectangleBuilder {
public:
    RectangleBuilder& name(std::string value);
    RectangleBuilder& width(double value);
    RectangleBuilder& height(double value);

    [[nodiscard]] builder_pattern_common::Rectangle build() const;

private:
    std::optional<std::string> name_;
    std::optional<double> width_;
    std::optional<double> height_;
};

}  // namespace builder_pattern_modern
