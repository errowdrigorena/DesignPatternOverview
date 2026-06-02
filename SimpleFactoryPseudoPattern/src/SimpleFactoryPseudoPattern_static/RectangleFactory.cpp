#include <SimpleFactoryPseudoPattern_static/RectangleFactory.hpp>

#include <Shapes_traditional/Rectangle.hpp>

namespace simple_factory_pseudo_pattern_static {

std::unique_ptr<shapes_traditional::Shapes> RectangleFactory::create() const
{
    return std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0);
}

}  // namespace simple_factory_pseudo_pattern_static
