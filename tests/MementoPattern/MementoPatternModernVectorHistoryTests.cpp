#include <MementoPattern_modern/vector_history/ShapeCanvas.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>

namespace {

using testing::ElementsAre;
using testing::Eq;

using memento_pattern_modern::vector_history::CanvasHistory;
using memento_pattern_modern::vector_history::ShapeCanvas;

TEST(ModernVectorHistoryMemento, StandardVectorCanActAsHistory)
{
    ShapeCanvas canvas;
    CanvasHistory history;

    history.push_back(canvas.snapshot());
    canvas.add_circle("sun", 10.0);
    history.push_back(canvas.snapshot());
    canvas.add_rectangle("ground", 100.0, 20.0);

    canvas.restore(history.back());
    history.pop_back();

    EXPECT_THAT(canvas.shape_names(), ElementsAre("sun"));
}

TEST(ModernVectorHistoryMemento, HistoryStoresSelectionSnapshots)
{
    ShapeCanvas canvas;
    CanvasHistory history;

    canvas.add_circle("sun", 10.0);
    canvas.select("sun");
    history.push_back(canvas.snapshot());
    canvas.add_rectangle("ground", 100.0, 20.0);
    canvas.select("ground");

    canvas.restore(history.back());

    EXPECT_THAT(canvas.selected_shape(), Eq(std::optional<std::string>{"sun"}));
}

TEST(ModernVectorHistoryMemento, HistoryUsesPlainSnapshots)
{
    ShapeCanvas canvas;
    CanvasHistory history;

    history.push_back(canvas.snapshot());

    EXPECT_EQ(history.back().shape_count(), 0);
}

}  // namespace
