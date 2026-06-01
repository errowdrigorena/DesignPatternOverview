#pragma once

#include <ostream>

namespace observer_pattern {

enum class Event_enum {
    add,
    remove
};

inline std::ostream& operator<<(std::ostream& os, const Event_enum event)
{
    switch (event) {
    case Event_enum::add:
        return os << "add";
    case Event_enum::remove:
        return os << "remove";
    }

    return os << "unknown event";
}

}  // namespace observer_pattern
