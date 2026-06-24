#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <memory>
#include <utility>
#include <vector>

namespace iterator_pattern_modern::iterators {

class ShapeCollection {
public:
    using iterator = std::vector<std::unique_ptr<shapes_traditional::Shape>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<shapes_traditional::Shape>>::const_iterator;

    void add(std::unique_ptr<shapes_traditional::Shape> shape);

    [[nodiscard]] std::pair<iterator, iterator> iterators() noexcept;
    [[nodiscard]] std::pair<const_iterator, const_iterator> iterators() const noexcept;

    // These alternatives require their definitions in this header so callers can deduce auto.
    // [[nodiscard]] auto iterators() noexcept
    // {
    //     return std::pair{shapes_.begin(), shapes_.end()};
    // }
    //
    // [[nodiscard]] auto iterators() const noexcept
    // {
    //     return std::pair{shapes_.cbegin(), shapes_.cend()};
    // }

private:
    std::vector<std::unique_ptr<shapes_traditional::Shape>> shapes_;
};

}  // namespace iterator_pattern_modern::iterators
