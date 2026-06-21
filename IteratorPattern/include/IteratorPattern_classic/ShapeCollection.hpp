#pragma once

#include <IteratorPattern_classic/Iterator.hpp>

#include <memory>
#include <string>
#include <vector>

namespace iterator_pattern_classic {

class ShapeCollection {
public:
    void add(std::unique_ptr<shapes_traditional::Shapes> shape);

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::unique_ptr<Iterator> create_iterator() const;

private:
    friend class ShapeCollectionIterator;

    std::vector<std::unique_ptr<shapes_traditional::Shapes>> shapes_;
};

}  // namespace iterator_pattern_classic
