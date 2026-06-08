#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace observer_pattern_modern {

template <typename... Args>
class Signal {
    struct Slot_entry;
    struct State;

public:
    using Slot = std::function<void(Args...)>;

    class Connection {
    public:
        Connection() = default;
        ~Connection()
        {
            disconnect();
        }

        Connection(const Connection&) = delete;
        Connection& operator=(const Connection&) = delete;

        Connection(Connection&& other) noexcept
            : state_{std::move(other.state_)}
            , id_{other.id_}
        {
            other.id_ = 0;
        }

        Connection& operator=(Connection&& other) noexcept
        {
            if (this != &other) {
                disconnect();

                state_ = std::move(other.state_);
                id_ = other.id_;

                other.id_ = 0;
            }

            return *this;
        }

        void disconnect()
        {
            if (const auto state = state_.lock()) {
                state->disconnect(id_);
            }

            state_.reset();
            id_ = 0;
        }

        [[nodiscard]] bool connected() const
        {
            if (const auto state = state_.lock()) {
                return state->connected(id_);
            }

            return false;
        }

    private:
        friend class Signal;

        Connection(std::weak_ptr<State> state, const std::size_t id)
            : state_{std::move(state)}
            , id_{id}
        {
        }

        std::weak_ptr<State> state_;
        std::size_t id_{0};
    };

    Signal()
        : state_{std::make_shared<State>()}
    {
    }

    [[nodiscard]] Connection connect(Slot slot)
    {
        if (!slot) {
            throw std::invalid_argument{"slot cannot be empty"};
        }

        const auto id = state_->next_id++;
        state_->slots.push_back(Slot_entry{id, std::move(slot)});

        return Connection{state_, id};
    }

    void emit(Args... args) const
    {
        const auto slots = state_->slots;

        for (const auto& slot : slots) {
            if (state_->connected(slot.id)) {
                slot.callback(args...);
            }
        }
    }

    void operator()(Args... args) const
    {
        emit(args...);
    }

private:
    struct Slot_entry {
        std::size_t id;
        Slot callback;
    };

    struct State {
        std::vector<Slot_entry> slots;
        std::size_t next_id{0};

        void disconnect(const std::size_t id)
        {
            std::erase_if(slots, [id](const Slot_entry& slot) {
                return slot.id == id;
            });
        }

        [[nodiscard]] bool connected(const std::size_t id) const
        {
            return std::ranges::any_of(slots, [id](const Slot_entry& slot) {
                return slot.id == id;
            });
        }
    };

    std::shared_ptr<State> state_;
};

}  // namespace observer_pattern_modern
