#include <DecoratorPattern_classic/Decorator.hpp>

namespace decorator_pattern_classic {

Decorator::Decorator(std::unique_ptr<Component> component)
    : component_(std::move(component))
{}

void Decorator::operation()
{
    component_->operation();
}

}  // namespace decorator_pattern_classic
