#include <SingletonPattern_classic/ApplicationLogger.hpp>
#include <SingletonPattern_modern/call_once/AuditTrail.hpp>
#include <SingletonPattern_modern/meyers/ApplicationSettings.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

namespace {

using testing::Eq;
using testing::HasSubstr;
using testing::IsFalse;
using testing::Optional;

using singleton_pattern_classic::ApplicationLogger;
using singleton_pattern_modern::call_once::AuditTrail;
using singleton_pattern_modern::meyers::ApplicationSettings;

TEST(ClassicSingletonLogger, ReturnsTheSameInstance)
{
    auto& first = ApplicationLogger::instance();
    auto& second = ApplicationLogger::instance();

    EXPECT_THAT(&first, Eq(&second));
}

TEST(ClassicSingletonLogger, LogIncrementsMessageCount)
{
    auto& logger = ApplicationLogger::instance();
    const auto before = logger.message_count();

    testing::internal::CaptureStdout();
    logger.log("counted message");
    testing::internal::GetCapturedStdout();

    EXPECT_THAT(logger.message_count(), Eq(before + 1));
}

TEST(ClassicSingletonLogger, UsesConfiguredPrefix)
{
    auto& logger = ApplicationLogger::instance();

    testing::internal::CaptureStdout();
    logger.set_prefix("test-prefix");
    logger.log("prefixed message");
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("[test-prefix] prefixed message"));
}

TEST(ClassicSingletonLogger, IsNotCopyConstructible)
{
    EXPECT_THAT(std::is_copy_constructible_v<ApplicationLogger>, IsFalse());
}

TEST(ClassicSingletonLogger, IsNotCopyAssignable)
{
    EXPECT_THAT(std::is_copy_assignable_v<ApplicationLogger>, IsFalse());
}

TEST(ClassicSingletonLogger, IsNotMoveConstructible)
{
    EXPECT_THAT(std::is_move_constructible_v<ApplicationLogger>, IsFalse());
}

TEST(ClassicSingletonLogger, IsNotMoveAssignable)
{
    EXPECT_THAT(std::is_move_assignable_v<ApplicationLogger>, IsFalse());
}

TEST(MeyersApplicationSettings, ReturnsTheSameInstance)
{
    auto& first = ApplicationSettings::instance();
    auto& second = ApplicationSettings::instance();

    EXPECT_THAT(&first, Eq(&second));
}

TEST(MeyersApplicationSettings, StoresAValue)
{
    auto& settings = ApplicationSettings::instance();

    settings.set("tests.singleton.store", "enabled");

    EXPECT_THAT(settings.value("tests.singleton.store"), Optional(Eq("enabled")));
}

TEST(MeyersApplicationSettings, UpdatesAValue)
{
    auto& settings = ApplicationSettings::instance();

    settings.set("tests.singleton.update", "before");
    settings.set("tests.singleton.update", "after");

    EXPECT_THAT(settings.value("tests.singleton.update"), Optional(Eq("after")));
}

TEST(MeyersApplicationSettings, ReturnsEmptyOptionalForMissingValue)
{
    const auto& settings = ApplicationSettings::instance();

    EXPECT_THAT(settings.value("tests.singleton.missing"), Eq(std::nullopt));
}

TEST(MeyersApplicationSettings, IsNotCopyConstructible)
{
    EXPECT_THAT(std::is_copy_constructible_v<ApplicationSettings>, IsFalse());
}

TEST(MeyersApplicationSettings, IsNotCopyAssignable)
{
    EXPECT_THAT(std::is_copy_assignable_v<ApplicationSettings>, IsFalse());
}

TEST(MeyersApplicationSettings, IsNotMoveConstructible)
{
    EXPECT_THAT(std::is_move_constructible_v<ApplicationSettings>, IsFalse());
}

TEST(MeyersApplicationSettings, IsNotMoveAssignable)
{
    EXPECT_THAT(std::is_move_assignable_v<ApplicationSettings>, IsFalse());
}

TEST(CallOnceAuditTrail, ReturnsTheSameInstance)
{
    auto& first = AuditTrail::instance();
    auto& second = AuditTrail::instance();

    EXPECT_THAT(&first, Eq(&second));
}

TEST(CallOnceAuditTrail, RecordIncrementsSize)
{
    auto& audit_trail = AuditTrail::instance();
    const auto before = audit_trail.size();

    audit_trail.record("single event");

    EXPECT_THAT(audit_trail.size(), Eq(before + 1));
}

TEST(CallOnceAuditTrail, RecordsEventsFromMultipleThreads)
{
    auto& audit_trail = AuditTrail::instance();
    const auto before = audit_trail.size();

    constexpr auto worker_count = 4;
    constexpr auto events_per_worker = 5;
    std::vector<std::thread> workers;

    for (auto worker_id = 0; worker_id < worker_count; ++worker_id) {
        workers.emplace_back([worker_id] {
            auto& thread_audit_trail = AuditTrail::instance();

            for (auto event_id = 0; event_id < events_per_worker; ++event_id) {
                thread_audit_trail.record(
                    "worker " + std::to_string(worker_id) + " event " + std::to_string(event_id));
            }
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }

    EXPECT_THAT(audit_trail.size(), Eq(before + (worker_count * events_per_worker)));
}

TEST(CallOnceAuditTrail, IsNotCopyConstructible)
{
    EXPECT_THAT(std::is_copy_constructible_v<AuditTrail>, IsFalse());
}

TEST(CallOnceAuditTrail, IsNotCopyAssignable)
{
    EXPECT_THAT(std::is_copy_assignable_v<AuditTrail>, IsFalse());
}

TEST(CallOnceAuditTrail, IsNotMoveConstructible)
{
    EXPECT_THAT(std::is_move_constructible_v<AuditTrail>, IsFalse());
}

TEST(CallOnceAuditTrail, IsNotMoveAssignable)
{
    EXPECT_THAT(std::is_move_assignable_v<AuditTrail>, IsFalse());
}

}  // namespace
