#include <MementoPattern_classic/CanvasHistory.hpp>

#include <stdexcept>
#include <utility>

namespace memento_pattern_classic {

void CanvasHistory::push(CanvasSnapshot snapshot)
{
    snapshots_.push_back(std::move(snapshot));
}

CanvasSnapshot CanvasHistory::pop()
{
    if(snapshots_.empty()) {
        throw std::out_of_range{"Cannot pop an empty canvas history"};
    }

    auto snapshot = snapshots_.back();
    snapshots_.pop_back();
    return snapshot;
}

bool CanvasHistory::empty() const
{
    return snapshots_.empty();
}

std::size_t CanvasHistory::size() const
{
    return snapshots_.size();
}

}  // namespace memento_pattern_classic
