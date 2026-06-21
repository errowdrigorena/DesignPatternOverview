#pragma once

#include <functional>

namespace mediator_pattern_modern {

class NumberField {
public:
    using ChangeHandler = std::function<void(double)>;

    NumberField(double initial_value, ChangeHandler on_change);

    [[nodiscard]] double value() const;

    void enter_value(double value);
    void set_value(double value);

private:
    double value_;
    ChangeHandler on_change_;
};

}  // namespace mediator_pattern_modern
