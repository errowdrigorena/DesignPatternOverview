#include <IteratorPattern_boost/ShapeCollection.hpp>

#include <stdexcept>
#include <utility>

namespace iterator_pattern_boost {

void ShapeCollection::add(std::unique_ptr<shapes_traditional::Shape> shape)
{
    if (!shape) {
        throw std::invalid_argument("A shape collection cannot contain null shapes");
    }

    shapes_.push_back(std::move(shape));
}

ShapeIterator ShapeCollection::begin() const noexcept
{
    return ShapeIterator{shapes_.cbegin()};
}

ShapeIterator ShapeCollection::end() const noexcept
{
    return ShapeIterator{shapes_.cend()};
}

}  // namespace iterator_pattern_boost
