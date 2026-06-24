#include <FactoryMethodPattern_classic/CircleCreator.hpp>

#include <Shapes_traditional/Circle.hpp>

namespace factory_method_pattern_classic {

std::unique_ptr<shapes_traditional::Shape> CircleCreator::create_shape() const
{
    return std::make_unique<shapes_traditional::Circle>(6.0);
}

}  // namespace factory_method_pattern_classic
