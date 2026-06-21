#include <MediatorPattern_modern/NumberField.hpp>

#include <stdexcept>
#include <utility>

namespace mediator_pattern_modern {

NumberField::NumberField(double initial_value, ChangeHandler on_change)
    : value_{initial_value}
    , on_change_{std::move(on_change)}
{
    if (initial_value <= 0.0) {
        throw std::invalid_argument{"A dimension must be positive"};
    }

    if (!on_change_) {
        throw std::invalid_argument{"A number field needs a change handler"};
    }
}

double NumberField::value() const
{
    return value_;
}

void NumberField::enter_value(double value)
{
    set_value(value);
    on_change_(value_);
}

void NumberField::set_value(double value)
{
    if (value <= 0.0) {
        throw std::invalid_argument{"A dimension must be positive"};
    }

    value_ = value;
}

}  // namespace mediator_pattern_modern
