#include <SingletonPattern_classic/ApplicationLogger.hpp>

#include <iostream>

namespace {

void load_user_profile()
{
    singleton_pattern_classic::ApplicationLogger::instance().log("loading user profile");
}

void connect_to_service()
{
    singleton_pattern_classic::ApplicationLogger::instance().log("connecting to service");
}

}  // namespace

int main()
{
    auto& logger = singleton_pattern_classic::ApplicationLogger::instance();

    logger.set_prefix("startup");
    logger.log("application started");

    load_user_profile();
    connect_to_service();

    std::cout << "Messages written: " << logger.message_count() << '\n';

    return 0;
}
