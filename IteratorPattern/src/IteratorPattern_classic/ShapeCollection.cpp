#include <IteratorPattern_classic/ShapeCollection.hpp>

#include <IteratorPattern_classic/ShapeCollectionIterator.hpp>

#include <stdexcept>

namespace iterator_pattern_classic {

void ShapeCollection::add(std::unique_ptr<shapes_traditional::Shape> shape)
{
    if (shape == nullptr) {
        throw std::invalid_argument{"A shape collection cannot contain null shapes"};
    }

    shapes_.push_back(std::move(shape));
}

std::size_t ShapeCollection::size() const
{
    return shapes_.size();
}

std::unique_ptr<Iterator> ShapeCollection::create_iterator() const
{
    return std::make_unique<ShapeCollectionIterator>(*this);
}

}  // namespace iterator_pattern_classic
