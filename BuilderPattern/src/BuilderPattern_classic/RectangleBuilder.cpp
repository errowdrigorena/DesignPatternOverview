#include <BuilderPattern_classic/ConcreteRectangleBuilder.hpp>

#include <cmath>
#include <stdexcept>
#include <utility>

namespace builder_pattern_classic {

void ConcreteRectangleBuilder::reset()
{
    name_.reset();
    width_.reset();
    height_.reset();
}

void ConcreteRectangleBuilder::set_name(const std::string_view name)
{
    name_ = std::string{name};
}

void ConcreteRectangleBuilder::set_width(const double width)
{
    width_ = width;
}

void ConcreteRectangleBuilder::set_height(const double height)
{
    height_ = height;
}

builder_pattern_common::Rectangle ConcreteRectangleBuilder::build() const
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

}  // namespace builder_pattern_classic
