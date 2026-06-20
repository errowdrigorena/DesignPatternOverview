#include <BuilderPattern_modern/RectangleBuilder.hpp>

#include <cmath>
#include <stdexcept>
#include <utility>

namespace builder_pattern_modern {

RectangleBuilder& RectangleBuilder::name(std::string value)
{
    name_ = std::move(value);
    return *this;
}

RectangleBuilder& RectangleBuilder::width(const double value)
{
    width_ = value;
    return *this;
}

RectangleBuilder& RectangleBuilder::height(const double value)
{
    height_ = value;
    return *this;
}

builder_pattern_common::Rectangle RectangleBuilder::build() const
{
    if (!name_.has_value() || name_->empty()) {
        throw std::logic_error{"Rectangle name is required"};
    }
    if (!width_.has_value() || !std::isfinite(*width_) || *width_ <= 0.0) {
        throw std::logic_error{"Rectangle width must be finite and positive"};
    }
    if (!height_.has_value() || !std::isfinite(*height_) || *height_ <= 0.0) {
        throw std::logic_error{"Rectangle height must be finite and positive"};
    }

    return builder_pattern_common::Rectangle{*name_, *width_, *height_};
}

}  // namespace builder_pattern_modern
