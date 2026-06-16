#include <MementoPattern_modern/nested_snapshot/ShapeCanvas.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>

namespace {

using testing::ElementsAre;
using testing::Eq;

using memento_pattern_modern::nested_snapshot::ShapeCanvas;

TEST(ModernNestedSnapshotMemento, RestoresShapeListFromNestedSnapshot)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);
    const ShapeCanvas::Snapshot snapshot = canvas.snapshot();

    canvas.add_rectangle("ground", 100.0, 20.0);
    canvas.restore(snapshot);

    EXPECT_THAT(canvas.shape_names(), ElementsAre("sun"));
}

TEST(ModernNestedSnapshotMemento, RestoresSelectionFromNestedSnapshot)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);
    canvas.select("sun");
    const ShapeCanvas::Snapshot snapshot = canvas.snapshot();

    canvas.add_rectangle("ground", 100.0, 20.0);
    canvas.select("ground");
    canvas.restore(snapshot);

    EXPECT_THAT(canvas.selected_shape(), Eq(std::optional<std::string>{"sun"}));
}

TEST(ModernNestedSnapshotMemento, SnapshotBelongsToTheCanvasType)
{
    ShapeCanvas canvas;
    canvas.add_circle("sun", 10.0);

    const ShapeCanvas::Snapshot snapshot = canvas.snapshot();

    EXPECT_EQ(snapshot.shape_count(), 1);
}

}  // namespace
