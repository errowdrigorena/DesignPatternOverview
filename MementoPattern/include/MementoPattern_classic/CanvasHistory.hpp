#pragma once

#include <MementoPattern_classic/ShapeCanvas.hpp>

#include <vector>

namespace memento_pattern_classic {

class CanvasHistory {
public:
    void push(CanvasSnapshot snapshot);
    [[nodiscard]] CanvasSnapshot pop();
    [[nodiscard]] bool empty() const;
    [[nodiscard]] std::size_t size() const;

private:
    std::vector<CanvasSnapshot> snapshots_;
};

}  // namespace memento_pattern_classic
