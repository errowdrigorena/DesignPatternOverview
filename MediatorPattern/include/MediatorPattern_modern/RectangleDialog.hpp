#pragma once

#include <MediatorPattern_modern/CheckBox.hpp>
#include <MediatorPattern_modern/NumberField.hpp>
#include <MediatorPattern_modern/RectanglePreview.hpp>

#include <iosfwd>

namespace mediator_pattern_modern {

class RectangleDialog {
public:
    RectangleDialog(double initial_width, double initial_height, std::ostream& output);

    RectangleDialog(const RectangleDialog&) = delete;
    RectangleDialog& operator=(const RectangleDialog&) = delete;
    RectangleDialog(RectangleDialog&&) = delete;
    RectangleDialog& operator=(RectangleDialog&&) = delete;

    NumberField& width_field();
    NumberField& height_field();
    CheckBox& keep_aspect_ratio_check_box();
    [[nodiscard]] const RectanglePreview& preview() const;

private:
    void width_changed();
    void height_changed();
    void refresh_preview();

    NumberField width_field_;
    NumberField height_field_;
    CheckBox keep_aspect_ratio_check_box_;
    RectanglePreview preview_;
    double aspect_ratio_;
};

}  // namespace mediator_pattern_modern
