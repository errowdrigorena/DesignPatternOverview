#include <MementoPattern_classic/CanvasHistory.hpp>
#include <MementoPattern_classic/ShapeCanvas.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <vector>

namespace {

using testing::ElementsAre;
using testing::Eq;

using memento_pattern_classic::CanvasHistory;
using memento_pattern_classic::ShapeCanvas;

TEST(ClassicMemento, RestoresShapeListWithoutExposingCanvasStorage)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);
    const auto snapshot = canvas.save();

    canvas.add_rectangle("ground", 100.0, 20.0);
    canvas.restore(snapshot);

    EXPECT_THAT(canvas.shape_names(), ElementsAre("sun"));
}

TEST(ClassicMemento, RestoresSelectedShape)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);
    canvas.select("sun");
    const auto snapshot = canvas.save();

    canvas.add_rectangle("ground", 100.0, 20.0);
    canvas.select("ground");
    canvas.restore(snapshot);

    EXPECT_THAT(canvas.selected_shape(), Eq(std::optional<std::string>{"sun"}));
}

TEST(ClassicMemento, HistorySupportsUndo)
{
    ShapeCanvas canvas;
    CanvasHistory history;

    history.push(canvas.save());
    canvas.add_circle("sun", 10.0);
    history.push(canvas.save());
    canvas.add_rectangle("ground", 100.0, 20.0);

    canvas.restore(history.pop());

    EXPECT_THAT(canvas.shape_names(), ElementsAre("sun"));
}

TEST(ClassicMemento, SelectingAnUnknownShapeFails)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);

    EXPECT_THROW(canvas.select("missing"), std::invalid_argument);
}

}  // namespace
