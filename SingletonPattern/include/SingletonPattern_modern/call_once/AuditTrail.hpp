#pragma once

#include <SingletonPattern_modern/call_once/CallOnceSingleton.hpp>

#include <cstddef>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

namespace singleton_pattern_modern::call_once {

class AuditTrail final : public CallOnceSingleton<AuditTrail> {
public:
    friend class CallOnceSingleton<AuditTrail>;

    void record(std::string_view event)
    {
        const std::lock_guard lock{mutex_};
        events_.emplace_back(event);
    }

    [[nodiscard]] std::size_t size() const
    {
        const std::lock_guard lock{mutex_};
        return events_.size();
    }

private:
    AuditTrail() = default;

    mutable std::mutex mutex_;
    std::vector<std::string> events_;
};

}  // namespace singleton_pattern_modern::call_once
