#include <MediatorPattern_modern/RectangleDialog.hpp>

#include <stdexcept>

namespace mediator_pattern_modern {

RectangleDialog::RectangleDialog(double initial_width, double initial_height, std::ostream& output)
    : width_field_{initial_width, [this](double) { width_changed(); }}
    , height_field_{initial_height, [this](double) { height_changed(); }}
    , keep_aspect_ratio_check_box_{[this](bool) { refresh_preview(); }}
    , preview_{output}
    , aspect_ratio_{initial_width / initial_height}
{
    if (initial_width <= 0.0 || initial_height <= 0.0) {
        throw std::invalid_argument{"Rectangle dimensions must be positive"};
    }
}

NumberField& RectangleDialog::width_field()
{
    return width_field_;
}

NumberField& RectangleDialog::height_field()
{
    return height_field_;
}

CheckBox& RectangleDialog::keep_aspect_ratio_check_box()
{
    return keep_aspect_ratio_check_box_;
}

const RectanglePreview& RectangleDialog::preview() const
{
    return preview_;
}

void RectangleDialog::width_changed()
{
    if (keep_aspect_ratio_check_box_.is_checked()) {
        height_field_.set_value(width_field_.value() / aspect_ratio_);
    }

    refresh_preview();
}

void RectangleDialog::height_changed()
{
    if (keep_aspect_ratio_check_box_.is_checked()) {
        width_field_.set_value(height_field_.value() * aspect_ratio_);
    }

    refresh_preview();
}

void RectangleDialog::refresh_preview()
{
    preview_.show(width_field_.value(), height_field_.value());
}

}  // namespace mediator_pattern_modern
