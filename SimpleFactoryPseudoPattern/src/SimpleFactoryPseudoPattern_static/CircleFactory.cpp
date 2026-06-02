#include <SimpleFactoryPseudoPattern_static/CircleFactory.hpp>

#include <Shapes_traditional/Circle.hpp>

namespace simple_factory_pseudo_pattern_static {

std::unique_ptr<shapes_traditional::Shapes> CircleFactory::create() const
{
    return std::make_unique<shapes_traditional::Circle>(6.0);
}

}  // namespace simple_factory_pseudo_pattern_static
