#include <CommandPattern_classic/Command.hpp>
#include <CommandPattern_classic/CommandHistory.hpp>
#include <CommandPattern_classic/DoBoringCommand.hpp>
#include <CommandPattern_classic/DoCoolCommand.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

using testing::ElementsAre;
using testing::HasSubstr;
using testing::IsEmpty;

using command_pattern_classic::DoBoringCommand;
using command_pattern_classic::DoCoolCommand;

class RecordingCommand final : public command_pattern_classic::Command {
public:
    RecordingCommand(std::vector<std::string>& events, std::string name)
        : events_{events}
        , name_{std::move(name)}
    {
    }

    void execute() override
    {
        events_.push_back("execute " + name_);
    }

    void undo() override
    {
        events_.push_back("undo " + name_);
    }

private:
    std::vector<std::string>& events_;
    std::string name_;
};

TEST(ClassicDoCoolCommand, ExecuteWritesMessage)
{
    DoCoolCommand command;

    testing::internal::CaptureStdout();
    command.execute();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("doing something cool"));
}

TEST(ClassicDoCoolCommand, UndoWritesMessage)
{
    DoCoolCommand command;

    testing::internal::CaptureStdout();
    command.undo();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("undoing something cool"));
}

TEST(ClassicDoBoringCommand, ExecuteWritesMessage)
{
    DoBoringCommand command;

    testing::internal::CaptureStdout();
    command.execute();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("doing something boring"));
}

TEST(ClassicDoBoringCommand, UndoWritesMessage)
{
    DoBoringCommand command;

    testing::internal::CaptureStdout();
    command.undo();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("undoing something boring"));
}

TEST(ClassicCommandHistory, ExecuteRunsCommand)
{
    command_pattern_classic::CommandHistory history;
    std::vector<std::string> events;

    history.execute(std::make_unique<RecordingCommand>(events, "alpha"));

    EXPECT_THAT(events, ElementsAre("execute alpha"));
}

TEST(ClassicCommandHistory, UndoLastRunsMostRecentCommandUndo)
{
    command_pattern_classic::CommandHistory history;
    std::vector<std::string> events;

    history.execute(std::make_unique<RecordingCommand>(events, "alpha"));
    history.execute(std::make_unique<RecordingCommand>(events, "beta"));
    history.undo_last();

    EXPECT_THAT(events, ElementsAre("execute alpha", "execute beta", "undo beta"));
}

TEST(ClassicCommandHistory, UndoLastRemovesUndoneCommand)
{
    command_pattern_classic::CommandHistory history;
    std::vector<std::string> events;

    history.execute(std::make_unique<RecordingCommand>(events, "alpha"));
    history.execute(std::make_unique<RecordingCommand>(events, "beta"));
    history.undo_last();
    history.undo_last();

    EXPECT_THAT(events, ElementsAre("execute alpha", "execute beta", "undo beta", "undo alpha"));
}

TEST(ClassicCommandHistory, UndoLastOnEmptyHistoryDoesNothing)
{
    command_pattern_classic::CommandHistory history;
    std::vector<std::string> events;

    history.undo_last();

    EXPECT_THAT(events, IsEmpty());
}

}  // namespace
