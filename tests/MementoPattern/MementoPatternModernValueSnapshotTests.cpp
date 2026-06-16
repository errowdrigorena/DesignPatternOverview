#include <MementoPattern_modern/value_snapshot/ShapeCanvas.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>

namespace {

using testing::ElementsAre;
using testing::Eq;

using memento_pattern_modern::value_snapshot::CanvasSnapshot;
using memento_pattern_modern::value_snapshot::ShapeCanvas;

TEST(ModernValueSnapshotMemento, RestoresShapeListFromSnapshot)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);
    const auto snapshot = canvas.snapshot();

    canvas.add_rectangle("ground", 100.0, 20.0);
    canvas.restore(snapshot);

    EXPECT_THAT(canvas.shape_names(), ElementsAre("sun"));
}

TEST(ModernValueSnapshotMemento, RestoresSelectedShapeFromSnapshot)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);
    canvas.select("sun");
    const auto snapshot = canvas.snapshot();

    canvas.add_rectangle("ground", 100.0, 20.0);
    canvas.select("ground");
    canvas.restore(snapshot);

    EXPECT_THAT(canvas.selected_shape(), Eq(std::optional<std::string>{"sun"}));
}

TEST(ModernValueSnapshotMemento, SnapshotCanBeUsedAsUndoToken)
{
    ShapeCanvas canvas;
    const CanvasSnapshot empty_canvas = canvas.snapshot();

    canvas.add_circle("sun", 10.0);
    canvas.restore(empty_canvas);

    EXPECT_TRUE(canvas.shape_names().empty());
}

TEST(ModernValueSnapshotMemento, SnapshotIsAPlainValue)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);

    CanvasSnapshot snapshot = canvas.snapshot();

    EXPECT_EQ(snapshot.shape_count(), 1);
}

}  // namespace
