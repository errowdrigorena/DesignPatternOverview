#include <SimpleFactoryPseudoPattern_map/ShapeFactory.hpp>

#include <Shapes_traditional/Circle.hpp>
#include <Shapes_traditional/Rectangle.hpp>
#include <Shapes_traditional/Triangle.hpp>

#include <functional>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

namespace simple_factory_pseudo_pattern_map {
namespace {

using ShapeCreator = std::function<std::unique_ptr<shapes_traditional::Shapes>()>;

const std::unordered_map<std::string_view, ShapeCreator> shape_creators{
    {"circle", [] {
         return std::make_unique<shapes_traditional::Circle>(6.0);
     }},
    {"rectangle", [] {
         return std::make_unique<shapes_traditional::Rectangle>(4.0, 3.0);
     }},
    {"triangle", [] {
         return std::make_unique<shapes_traditional::Triangle>(4.0, 3.0);
     }},
};

}  // namespace

std::unique_ptr<shapes_traditional::Shapes> ShapeFactory::create(
    const std::string_view shape_name) const
{
    const auto shape_creator = shape_creators.find(shape_name);

    if (shape_creator == shape_creators.end()) {
        throw std::invalid_argument{"unknown shape name"};
    }

    return shape_creator->second();
}

}  // namespace simple_factory_pseudo_pattern_map
