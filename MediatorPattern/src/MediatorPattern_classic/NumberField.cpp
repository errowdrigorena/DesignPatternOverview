#include <MediatorPattern_classic/NumberField.hpp>

#include <stdexcept>

namespace mediator_pattern_classic {

NumberField::NumberField(Mediator& mediator, double initial_value)
    : Component{mediator}
    , value_{initial_value}
{
    if (initial_value <= 0.0) {
        throw std::invalid_argument{"A dimension must be positive"};
    }
}

double NumberField::value() const
{
    return value_;
}

void NumberField::enter_value(double value)
{
    set_value(value);
    mediator_.notify(*this, ComponentEvent::value_changed);
}

void NumberField::set_value(double value)
{
    if (value <= 0.0) {
        throw std::invalid_argument{"A dimension must be positive"};
    }

    value_ = value;
}

}  // namespace mediator_pattern_classic
