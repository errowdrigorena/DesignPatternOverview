#include <MediatorPattern_modern/CheckBox.hpp>

#include <stdexcept>
#include <utility>

namespace mediator_pattern_modern {

CheckBox::CheckBox(ToggleHandler on_toggle, bool checked)
    : checked_{checked}
    , on_toggle_{std::move(on_toggle)}
{
    if (!on_toggle_) {
        throw std::invalid_argument{"A check box needs a toggle handler"};
    }
}

bool CheckBox::is_checked() const
{
    return checked_;
}

void CheckBox::toggle()
{
    checked_ = !checked_;
    on_toggle_(checked_);
}

}  // namespace mediator_pattern_modern
