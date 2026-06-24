#include <SimpleFactoryPseudoPattern_static/TriangleFactory.hpp>

#include <Shapes_traditional/Triangle.hpp>

namespace simple_factory_pseudo_pattern_static {

std::unique_ptr<shapes_traditional::Shape> TriangleFactory::create() const
{
    return std::make_unique<shapes_traditional::Triangle>(4.0, 3.0);
}

}  // namespace simple_factory_pseudo_pattern_static
