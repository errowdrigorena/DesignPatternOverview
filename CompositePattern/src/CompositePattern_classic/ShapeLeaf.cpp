#include <CompositePattern_classic/ShapeLeaf.hpp>

#include <ostream>
#include <stdexcept>
#include <utility>

namespace composite_pattern_classic {

ShapeLeaf::ShapeLeaf(std::string name, const double area)
    : name_{std::move(name)}
    , area_{area}
{
    if (name_.empty()) {
        throw std::invalid_argument("A shape leaf requires a name");
    }

    if (area_ < 0.0) {
        throw std::invalid_argument("A shape leaf area cannot be negative");
    }
}

double ShapeLeaf::area() const
{
    return area_;
}

void ShapeLeaf::render(std::ostream& output, const int depth) const
{
    output << std::string(static_cast<std::size_t>(depth) * 2U, ' ') << "- " << name_ << " (" << area_ << ")\n";
}

}  // namespace composite_pattern_classic
