#include <MementoPattern_modern/persistent/ShapeCanvas.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace memento_pattern_modern::persistent {

ShapeCanvas::ShapeCanvas(std::vector<ShapeRecord> shapes, std::optional<std::string> selected_shape)
    : shapes_{std::move(shapes)}
    , selected_shape_{std::move(selected_shape)}
{
}

ShapeCanvas ShapeCanvas::added_circle(std::string name, double radius) const
{
    auto shapes = shapes_;
    shapes.push_back(ShapeRecord{ShapeKind::circle, std::move(name), radius, 0.0});
    return ShapeCanvas{std::move(shapes), selected_shape_};
}

ShapeCanvas ShapeCanvas::added_rectangle(std::string name, double width, double height) const
{
    auto shapes = shapes_;
    shapes.push_back(ShapeRecord{ShapeKind::rectangle, std::move(name), width, height});
    return ShapeCanvas{std::move(shapes), selected_shape_};
}

ShapeCanvas ShapeCanvas::selected(const std::string& name) const
{
    if(!contains_shape(name)) {
        throw std::invalid_argument{"Cannot select an unknown shape"};
    }

    return ShapeCanvas{shapes_, name};
}

std::vector<std::string> ShapeCanvas::shape_names() const
{
    std::vector<std::string> names;
    names.reserve(shapes_.size());

    for(const auto& shape : shapes_) {
        names.push_back(shape.name);
    }

    return names;
}

std::optional<std::string> ShapeCanvas::selected_shape() const
{
    return selected_shape_;
}

bool ShapeCanvas::contains_shape(const std::string& name) const
{
    return std::ranges::any_of(
        shapes_,
        [&name](const ShapeRecord& shape) {
            return shape.name == name;
        });
}

}  // namespace memento_pattern_modern::persistent
