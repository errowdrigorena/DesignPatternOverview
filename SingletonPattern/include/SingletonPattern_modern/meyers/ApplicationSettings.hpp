#pragma once

#include <SingletonPattern_modern/meyers/MeyersSingleton.hpp>

#include <mutex>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace singleton_pattern_modern::meyers {

class ApplicationSettings final : public MeyersSingleton<ApplicationSettings> {
public:
    friend class MeyersSingleton<ApplicationSettings>;

    void set(std::string key, std::string value)
    {
        const std::lock_guard lock{mutex_};
        values_.insert_or_assign(std::move(key), std::move(value));
    }

    [[nodiscard]] std::optional<std::string> value(const std::string_view key) const
    {
        const std::lock_guard lock{mutex_};
        const auto it = values_.find(std::string{key});

        if (it == values_.end()) {
            return std::nullopt;
        }

        return it->second;
    }

private:
    ApplicationSettings() = default;

    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::string> values_;
};

}  // namespace singleton_pattern_modern::meyers
