#pragma once

#include <BuilderPattern_classic/RectangleBuilder.hpp>
#include <BuilderPattern_common/Rectangle.hpp>

#include <optional>
#include <string>

namespace builder_pattern_classic {

class ConcreteRectangleBuilder final : public RectangleBuilder {
public:
    void reset() override;
    void set_name(std::string_view name) override;
    void set_width(double width) override;
    void set_height(double height) override;

    [[nodiscard]] builder_pattern_common::Rectangle build() const;

private:
    std::optional<std::string> name_;
    std::optional<double> width_;
    std::optional<double> height_;
};

}  // namespace builder_pattern_classic
