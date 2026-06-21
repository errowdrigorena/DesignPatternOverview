#pragma once

#include <MediatorPattern_classic/Component.hpp>

namespace mediator_pattern_classic {

class CheckBox final : public Component {
public:
    explicit CheckBox(Mediator& mediator, bool checked = false);

    [[nodiscard]] bool is_checked() const;

    void toggle();

private:
    bool checked_;
};

}  // namespace mediator_pattern_classic
