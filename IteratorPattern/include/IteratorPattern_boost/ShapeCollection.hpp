#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <memory>
#include <vector>

namespace iterator_pattern_boost {

// boost::iterator_facade generates all iterator operators from just three
// primitives: dereference(), equal(), and increment()/decrement().
class ShapeIterator
    : public boost::iterator_facade<
          ShapeIterator,
          shapes_traditional::Shape const,
          boost::bidirectional_traversal_tag>
{
    using Underlying = std::vector<std::unique_ptr<shapes_traditional::Shape>>::const_iterator;

public:
    ShapeIterator() = default;
    explicit ShapeIterator(Underlying it) : it_{it} {}

private:
    friend class boost::iterator_core_access;

    reference dereference() const { return **it_; }
    bool equal(const ShapeIterator& other) const { return it_ == other.it_; }
    void increment() { ++it_; }
    void decrement() { --it_; }

    Underlying it_;
};

class ShapeCollection {
public:
    void add(std::unique_ptr<shapes_traditional::Shape> shape);

    [[nodiscard]] ShapeIterator begin() const noexcept;
    [[nodiscard]] ShapeIterator end() const noexcept;

private:
    std::vector<std::unique_ptr<shapes_traditional::Shape>> shapes_;
};

}  // namespace iterator_pattern_boost
