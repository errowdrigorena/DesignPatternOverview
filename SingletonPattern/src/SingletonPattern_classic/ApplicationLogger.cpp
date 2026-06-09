#include <SingletonPattern_classic/ApplicationLogger.hpp>

#include <iostream>
#include <utility>

namespace singleton_pattern_classic {

std::unique_ptr<ApplicationLogger> ApplicationLogger::instance_{nullptr};

ApplicationLogger& ApplicationLogger::instance()
{
    if (instance_ == nullptr) {
        instance_.reset(new ApplicationLogger{});
    }

    return *instance_;
}

void ApplicationLogger::set_prefix(std::string prefix)
{
    prefix_ = std::move(prefix);
}

void ApplicationLogger::log(const std::string_view message)
{
    ++message_count_;
    std::cout << '[' << prefix_ << "] " << message << '\n';
}

std::size_t ApplicationLogger::message_count() const
{
    return message_count_;
}

}  // namespace singleton_pattern_classic
