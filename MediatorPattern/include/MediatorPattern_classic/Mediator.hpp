#pragma once

namespace mediator_pattern_classic {

class Component;

enum class ComponentEvent {
    value_changed,
    toggled,
};

class Mediator {
public:
    virtual ~Mediator() = default;

    virtual void notify(Component& sender, ComponentEvent event) = 0;
};

}  // namespace mediator_pattern_classic
