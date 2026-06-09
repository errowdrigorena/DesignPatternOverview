#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>

namespace singleton_pattern_classic {

class ApplicationLogger final {
public:
    [[nodiscard]] static ApplicationLogger& instance();

    ApplicationLogger(const ApplicationLogger&) = delete;
    ApplicationLogger& operator=(const ApplicationLogger&) = delete;
    ApplicationLogger(ApplicationLogger&&) = delete;
    ApplicationLogger& operator=(ApplicationLogger&&) = delete;

    void set_prefix(std::string prefix);
    void log(std::string_view message);

    [[nodiscard]] std::size_t message_count() const;

private:
    ApplicationLogger() = default;

    static std::unique_ptr<ApplicationLogger> instance_;

    std::string prefix_{"classic"};
    std::size_t message_count_{0};
};

}  // namespace singleton_pattern_classic
