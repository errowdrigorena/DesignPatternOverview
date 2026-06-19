#include <FactoryMethodPattern_classic/RectangleCreator.hpp>

#include <Shapes_traditional/Rectangle.hpp>

namespace factory_method_pattern_classic {

std::unique_ptr<shapes_traditional::Shapes> RectangleCreator::create_shape() const
{
    return std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0);
}

}  // namespace factory_method_pattern_classic
