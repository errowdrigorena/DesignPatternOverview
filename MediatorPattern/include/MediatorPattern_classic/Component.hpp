#pragma once

#include <MediatorPattern_classic/Mediator.hpp>

namespace mediator_pattern_classic {

class Component {
public:
    explicit Component(Mediator& mediator);
    virtual ~Component() = default;

protected:
    Mediator& mediator_;
};

}  // namespace mediator_pattern_classic
