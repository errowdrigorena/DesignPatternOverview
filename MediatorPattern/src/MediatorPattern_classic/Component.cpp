#include <MediatorPattern_classic/Component.hpp>

namespace mediator_pattern_classic {

Component::Component(Mediator& mediator)
    : mediator_{mediator}
{
}

}  // namespace mediator_pattern_classic
