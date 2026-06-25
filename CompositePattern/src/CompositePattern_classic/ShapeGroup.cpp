#include <CompositePattern_classic/ShapeGroup.hpp>

#include <ostream>
#include <stdexcept>
#include <utility>

namespace composite_pattern_classic {

ShapeGroup::ShapeGroup(std::string name)
    : name_{std::move(name)}
{
    if (name_.empty()) {
        throw std::invalid_argument("A shape group requires a name");
    }
}

void ShapeGroup::add(std::unique_ptr<Graphic> graphic)
{
    if (!graphic) {
        throw std::invalid_argument("Cannot add a null graphic to a shape group");
    }

    children_.push_back(std::move(graphic));
}

std::size_t ShapeGroup::child_count() const
{
    return children_.size();
}

double ShapeGroup::area() const
{
    double total{};
    for (const auto& child : children_) {
        total += child->area();
    }

    return total;
}

void ShapeGroup::render(std::ostream& output, const int depth) const
{
    output << std::string(static_cast<std::size_t>(depth) * 2U, ' ') << "+ " << name_ << " (" << area() << ")\n";

    for (const auto& child : children_) {
        child->render(output, depth + 1);
    }
}

}  // namespace composite_pattern_classic
