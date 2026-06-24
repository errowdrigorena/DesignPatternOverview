#pragma once

#include <Shapes_traditional/Shape.hpp>

#include <memory>
#include <ranges>
#include <stdexcept>
#include <utility>
#include <vector>

namespace iterator_pattern_modern::ranges {

class ShapeCollection {
public:
    void add(std::unique_ptr<shapes_traditional::Shape> shape)
    {
        if (!shape) {
            throw std::invalid_argument("A shape collection cannot contain null shapes");
        }

        shapes_.push_back(std::move(shape));
    }

    [[nodiscard]] auto shapes() const
    {
        return shapes_ | std::views::transform([](const auto& shape) -> const shapes_traditional::Shape& {
                   return *shape;
               });
    }

private:
    std::vector<std::unique_ptr<shapes_traditional::Shape>> shapes_;
};

}  // namespace iterator_pattern_modern::ranges
