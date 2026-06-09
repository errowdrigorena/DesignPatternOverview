#include <SingletonPattern_modern/call_once/AuditTrail.hpp>
#include <SingletonPattern_modern/meyers/ApplicationSettings.hpp>

#include <iostream>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace {

void print_setting(const std::string_view key)
{
    const auto value = singleton_pattern_modern::meyers::ApplicationSettings::instance().value(key);

    if (value.has_value()) {
        std::cout << key << ": " << *value << '\n';
        return;
    }

    std::cout << key << ": <missing>\n";
}

void configure_feature_flags()
{
    auto& settings = singleton_pattern_modern::meyers::ApplicationSettings::instance();

    settings.set("feature.checkout", "enabled");
    settings.set("feature.dark_mode", "disabled");
}

void record_worker_events(const int worker_id)
{
    auto& audit_trail = singleton_pattern_modern::call_once::AuditTrail::instance();

    audit_trail.record("worker " + std::to_string(worker_id) + " started");
    audit_trail.record("worker " + std::to_string(worker_id) + " finished");
}

}  // namespace

int main()
{
    auto& settings = singleton_pattern_modern::meyers::ApplicationSettings::instance();

    settings.set("application.name", "DesignPatternOverview");
    settings.set("environment", "development");

    configure_feature_flags();

    print_setting("application.name");
    print_setting("environment");
    print_setting("feature.checkout");
    print_setting("feature.dark_mode");

    std::vector<std::thread> workers;

    for (auto worker_id = 0; worker_id < 4; ++worker_id) {
        workers.emplace_back(record_worker_events, worker_id);
    }

    for (auto& worker : workers) {
        worker.join();
    }

    const auto& audit_trail = singleton_pattern_modern::call_once::AuditTrail::instance();

    std::cout << "Settings instance: " << static_cast<const void*>(&settings) << '\n';
    std::cout << "Audit trail instance: " << static_cast<const void*>(&audit_trail) << '\n';
    std::cout << "Audit events: " << audit_trail.size() << '\n';

    return 0;
}
