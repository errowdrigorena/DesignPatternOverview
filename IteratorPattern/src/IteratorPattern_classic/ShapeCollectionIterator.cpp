#include <IteratorPattern_classic/ShapeCollectionIterator.hpp>

#include <stdexcept>

namespace iterator_pattern_classic {

ShapeCollectionIterator::ShapeCollectionIterator(const ShapeCollection& collection)
    : collection_{collection}
{
}

void ShapeCollectionIterator::first()
{
    current_index_ = 0U;
}

void ShapeCollectionIterator::next()
{
    if (!is_done()) {
        ++current_index_;
    }
}

bool ShapeCollectionIterator::is_done() const
{
    return current_index_ >= collection_.shapes_.size();
}

const shapes_traditional::Shape& ShapeCollectionIterator::current_item() const
{
    if (is_done()) {
        throw std::out_of_range{"Cannot read past the end of a shape collection"};
    }

    return *collection_.shapes_[current_index_];
}

}  // namespace iterator_pattern_classic
