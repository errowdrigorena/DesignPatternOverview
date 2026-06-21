#include <MediatorPattern_classic/CheckBox.hpp>

namespace mediator_pattern_classic {

CheckBox::CheckBox(Mediator& mediator, bool checked)
    : Component{mediator}
    , checked_{checked}
{
}

bool CheckBox::is_checked() const
{
    return checked_;
}

void CheckBox::toggle()
{
    checked_ = !checked_;
    mediator_.notify(*this, ComponentEvent::toggled);
}

}  // namespace mediator_pattern_classic
