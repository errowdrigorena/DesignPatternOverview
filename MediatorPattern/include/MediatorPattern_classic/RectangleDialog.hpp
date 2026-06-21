#pragma once

#include <MediatorPattern_classic/CheckBox.hpp>
#include <MediatorPattern_classic/Mediator.hpp>
#include <MediatorPattern_classic/NumberField.hpp>
#include <MediatorPattern_classic/RectanglePreview.hpp>

#include <iosfwd>

namespace mediator_pattern_classic {

class RectangleDialog final : public Mediator {
public:
    RectangleDialog(double initial_width, double initial_height, std::ostream& output);

    NumberField& width_field();
    NumberField& height_field();
    CheckBox& keep_aspect_ratio_check_box();
    [[nodiscard]] const RectanglePreview& preview() const;

    void notify(Component& sender, ComponentEvent event) override;

private:
    NumberField width_field_;
    NumberField height_field_;
    CheckBox keep_aspect_ratio_check_box_;
    RectanglePreview preview_;
    double aspect_ratio_;
};

}  // namespace mediator_pattern_classic
