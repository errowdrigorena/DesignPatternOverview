#include <FactoryMethodPattern_classic/TriangleCreator.hpp>

#include <Shapes_traditional/Triangle.hpp>

namespace factory_method_pattern_classic {

std::unique_ptr<shapes_traditional::Shape> TriangleCreator::create_shape() const
{
    return std::make_unique<shapes_traditional::Triangle>(4.0, 3.0);
}

}  // namespace factory_method_pattern_classic
