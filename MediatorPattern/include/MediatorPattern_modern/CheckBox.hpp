#pragma once

#include <functional>

namespace mediator_pattern_modern {

class CheckBox {
public:
    using ToggleHandler = std::function<void(bool)>;

    explicit CheckBox(ToggleHandler on_toggle, bool checked = false);

    [[nodiscard]] bool is_checked() const;

    void toggle();

private:
    bool checked_;
    ToggleHandler on_toggle_;
};

}  // namespace mediator_pattern_modern
