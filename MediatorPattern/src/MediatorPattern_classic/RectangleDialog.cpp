#include <MediatorPattern_classic/RectangleDialog.hpp>

#include <stdexcept>

namespace mediator_pattern_classic {

RectangleDialog::RectangleDialog(double initial_width, double initial_height, std::ostream& output)
    : width_field_{*this, initial_width}
    , height_field_{*this, initial_height}
    , keep_aspect_ratio_check_box_{*this}
    , preview_{*this, output}
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

void RectangleDialog::notify(Component& sender, ComponentEvent event)
{
    if (event == ComponentEvent::value_changed && keep_aspect_ratio_check_box_.is_checked()) {
        if (&sender == &width_field_) {
            height_field_.set_value(width_field_.value() / aspect_ratio_);
        } else if (&sender == &height_field_) {
            width_field_.set_value(height_field_.value() * aspect_ratio_);
        }
    }

    preview_.show(width_field_.value(), height_field_.value());
}

}  // namespace mediator_pattern_classic
