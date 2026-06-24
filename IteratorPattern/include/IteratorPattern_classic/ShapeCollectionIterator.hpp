#pragma once

#include <IteratorPattern_classic/Iterator.hpp>
#include <IteratorPattern_classic/ShapeCollection.hpp>

#include <cstddef>

namespace iterator_pattern_classic {

class ShapeCollectionIterator final : public Iterator {
public:
    explicit ShapeCollectionIterator(const ShapeCollection& collection);

    void first() override;
    void next() override;
    [[nodiscard]] bool is_done() const override;
    [[nodiscard]] const shapes_traditional::Shape& current_item() const override;

private:
    const ShapeCollection& collection_;
    std::size_t current_index_{};
};

}  // namespace iterator_pattern_classic
