#include <IteratorPattern_modern/iterators/ShapeCollection.hpp>

#include <stdexcept>
#include <utility>

namespace iterator_pattern_modern::iterators {

void ShapeCollection::add(std::unique_ptr<shapes_traditional::Shape> shape)
{
    if (!shape) {
        throw std::invalid_argument("A shape collection cannot contain null shapes");
    }

    shapes_.push_back(std::move(shape));
}

std::pair<ShapeCollection::iterator, ShapeCollection::iterator> ShapeCollection::iterators() noexcept
{
    return {shapes_.begin(), shapes_.end()};
}

std::pair<ShapeCollection::const_iterator, ShapeCollection::const_iterator> ShapeCollection::iterators() const noexcept
{
    return {shapes_.cbegin(), shapes_.cend()};
}

}  // namespace iterator_pattern_modern::iterators
