#pragma once
#include <cstddef>
#include <concepts>
#include <mutex>
#include <optional>
#include <limits>
#include <algorithm>
#include <utility>
#include <vector>

// Event wrapper that supports stable priority ordering.
// Lower priority value = processed first (i.e. priority 0 beats priority 10).
// Equal-priority events are processed in insertion order (FIFO).
template<typename EventT, std::totally_ordered PriorityT = int>
struct TPrioritizedEvent
{
    EventT      event;
    PriorityT   priority;
    std::size_t insertionOrder;

    bool operator<(const TPrioritizedEvent& other) const
    {
        if (priority != other.priority)
            return priority > other.priority;   // lower value = higher priority

        // Break ties FIFO: earlier-inserted event is "larger" in the max-heap → processed first.
        // maybeReset() renumbers well before the counter can wrap, so the
        // ordinary ordering is sufficient and remains a strict weak ordering.
        return insertionOrder > other.insertionOrder;
    }
};

// Thread-safe priority queue for events.
template<typename EventT, std::totally_ordered PriorityT = int>
class TEventQueue
{
public:
    using EventType    = EventT;
    using PriorityType = PriorityT;
    using ValueType    = TPrioritizedEvent<EventType, PriorityType>;

    void Push(const EventType& ev, const PriorityType& priority)
    {
        std::lock_guard lock(mutex_);
        maybeReset();
        queue_.emplace_back(ValueType{ev, priority, counter_++});
        std::push_heap(queue_.begin(), queue_.end());
    }

    void Push(EventType&& ev, PriorityType&& priority)
    {
        std::lock_guard lock(mutex_);
        maybeReset();
        queue_.emplace_back(ValueType{std::move(ev), std::move(priority), counter_++});
        std::push_heap(queue_.begin(), queue_.end());
    }

    std::pair<std::optional<EventType>, PriorityType> Pop()
    {
        std::lock_guard lock(mutex_);
        if (queue_.empty())
            return {std::nullopt, PriorityType{}};
        std::pop_heap(queue_.begin(), queue_.end());
        ValueType top = std::move(queue_.back());
        queue_.pop_back();
        return {std::move(top.event), std::move(top.priority)};
    }

    [[nodiscard]] bool        Empty() const { std::lock_guard lock(mutex_); return queue_.empty(); }
    [[nodiscard]] std::size_t Size()  const { std::lock_guard lock(mutex_); return queue_.size(); }

    // Drops all queued work. Used by TFSMOrchestrator to fail an entire batch
    // when processing one of its events throws.
    void Clear()
    {
        std::lock_guard lock(mutex_);
        queue_.clear();
    }

    TEventQueue() = default;

    TEventQueue(const TEventQueue& other)
    {
        std::lock_guard lock(other.mutex_);
        queue_   = other.queue_;
        counter_ = other.counter_;
    }

    TEventQueue& operator=(const TEventQueue& other)
    {
        if (this != &other)
        {
            std::scoped_lock lock(mutex_, other.mutex_);
            queue_   = other.queue_;
            counter_ = other.counter_;
        }
        return *this;
    }

    TEventQueue(TEventQueue&& other)
    {
        std::lock_guard lock(other.mutex_);
        queue_   = std::move(other.queue_);
        counter_ = other.counter_;
        other.counter_ = 0;
    }

    TEventQueue& operator=(TEventQueue&& other)
    {
        if (this != &other)
        {
            std::scoped_lock lock(mutex_, other.mutex_);
            queue_   = std::move(other.queue_);
            counter_ = other.counter_;
            other.counter_ = 0;
        }
        return *this;
    }

private:
    void maybeReset()
    {
        if (counter_ <= (std::numeric_limits<std::size_t>::max() >> 1))
            return;

        std::vector<ValueType> tmp;
        while (!queue_.empty())
        {
            std::pop_heap(queue_.begin(), queue_.end());
            tmp.push_back(std::move(queue_.back()));
            queue_.pop_back();
        }
        counter_ = 0;
        for (auto& item : tmp)
        {
            item.insertionOrder = counter_++;
            queue_.emplace_back(std::move(item));
            std::push_heap(queue_.begin(), queue_.end());
        }
    }

    mutable std::mutex                    mutex_;
    std::vector<ValueType>                queue_;  // maintained as a max-heap
    std::size_t                           counter_ = 0;
};
