#include <CommandPattern_modern/Command.hpp>
#include <CommandPattern_modern/CommandHistory.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

namespace {

using testing::ElementsAre;
using testing::IsEmpty;
using testing::Throws;

TEST(ModernCommand, ExecuteRunsAction)
{
    std::vector<std::string> events;
    command_pattern_modern::Command command{
        [&events] {
            events.emplace_back("execute");
        },
        [] {
        }};

    command.execute();

    EXPECT_THAT(events, ElementsAre("execute"));
}

TEST(ModernCommand, UndoRunsAction)
{
    std::vector<std::string> events;
    command_pattern_modern::Command command{
        [] {
        },
        [&events] {
            events.emplace_back("undo");
        }};

    command.undo();

    EXPECT_THAT(events, ElementsAre("undo"));
}

TEST(ModernCommand, RejectsEmptyExecuteAction)
{
    const auto create_command = [] {
        const command_pattern_modern::Command command{
            command_pattern_modern::Command::Action{},
            [] {
            }};
    };

    EXPECT_THAT(create_command, Throws<std::invalid_argument>());
}

TEST(ModernCommand, RejectsEmptyUndoAction)
{
    const auto create_command = [] {
        const command_pattern_modern::Command command{
            [] {
            },
            command_pattern_modern::Command::Action{}};
    };

    EXPECT_THAT(create_command, Throws<std::invalid_argument>());
}

TEST(ModernCommandHistory, ExecuteRunsCommand)
{
    command_pattern_modern::CommandHistory history;
    std::vector<std::string> events;

    history.execute(command_pattern_modern::Command{
        [&events] {
            events.emplace_back("execute alpha");
        },
        [] {
        }});

    EXPECT_THAT(events, ElementsAre("execute alpha"));
}

TEST(ModernCommandHistory, UndoLastRunsMostRecentCommandUndo)
{
    command_pattern_modern::CommandHistory history;
    std::vector<std::string> events;

    history.execute(command_pattern_modern::Command{
        [&events] {
            events.emplace_back("execute alpha");
        },
        [&events] {
            events.emplace_back("undo alpha");
        }});
    history.execute(command_pattern_modern::Command{
        [&events] {
            events.emplace_back("execute beta");
        },
        [&events] {
            events.emplace_back("undo beta");
        }});
    history.undo_last();

    EXPECT_THAT(events, ElementsAre("execute alpha", "execute beta", "undo beta"));
}

TEST(ModernCommandHistory, UndoLastRemovesUndoneCommand)
{
    command_pattern_modern::CommandHistory history;
    std::vector<std::string> events;

    history.execute(command_pattern_modern::Command{
        [&events] {
            events.emplace_back("execute alpha");
        },
        [&events] {
            events.emplace_back("undo alpha");
        }});
    history.execute(command_pattern_modern::Command{
        [&events] {
            events.emplace_back("execute beta");
        },
        [&events] {
            events.emplace_back("undo beta");
        }});
    history.undo_last();
    history.undo_last();

    EXPECT_THAT(events, ElementsAre("execute alpha", "execute beta", "undo beta", "undo alpha"));
}

TEST(ModernCommandHistory, UndoLastOnEmptyHistoryDoesNothing)
{
    command_pattern_modern::CommandHistory history;
    std::vector<std::string> events;

    history.undo_last();

    EXPECT_THAT(events, IsEmpty());
}

}  // namespace
