#pragma once

#include <MediatorPattern_classic/Component.hpp>

namespace mediator_pattern_classic {

class NumberField final : public Component {
public:
    explicit NumberField(Mediator& mediator, double initial_value);

    [[nodiscard]] double value() const;

    void enter_value(double value);
    void set_value(double value);

private:
    double value_;
};

}  // namespace mediator_pattern_classic
