#include <MediatorPattern_classic/RectangleDialog.hpp>

#include <iostream>

int main()
{
    mediator_pattern_classic::RectangleDialog dialog{4.0, 2.0, std::cout};

    dialog.width_field().enter_value(6.0);
    dialog.keep_aspect_ratio_check_box().toggle();
    dialog.width_field().enter_value(12.0);
    dialog.height_field().enter_value(5.0);
}
