#include <MementoPattern_classic/ShapeCanvas.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace memento_pattern_classic {

CanvasSnapshot::CanvasSnapshot(std::vector<ShapeRecord> shapes, std::optional<std::string> selected_shape)
    : shapes_{std::move(shapes)}
    , selected_shape_{std::move(selected_shape)}
{
}

std::size_t CanvasSnapshot::shape_count() const
{
    return shapes_.size();
}

void ShapeCanvas::add_circle(std::string name, double radius)
{
    shapes_.push_back(ShapeRecord{ShapeKind::circle, std::move(name), radius, 0.0});
}

void ShapeCanvas::add_rectangle(std::string name, double width, double height)
{
    shapes_.push_back(ShapeRecord{ShapeKind::rectangle, std::move(name), width, height});
}

void ShapeCanvas::select(const std::string& name)
{
    if(!contains_shape(name)) {
        throw std::invalid_argument{"Cannot select an unknown shape"};
    }

    selected_shape_ = name;
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

CanvasSnapshot ShapeCanvas::save() const
{
    return CanvasSnapshot{shapes_, selected_shape_};
}

void ShapeCanvas::restore(const CanvasSnapshot& snapshot)
{
    shapes_ = snapshot.shapes_;
    selected_shape_ = snapshot.selected_shape_;
}

bool ShapeCanvas::contains_shape(const std::string& name) const
{
    return std::ranges::any_of(
        shapes_,
        [&name](const ShapeRecord& shape) {
            return shape.name == name;
        });
}

}  // namespace memento_pattern_classic
