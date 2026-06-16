#include <MementoPattern_modern/persistent/ShapeCanvas.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <vector>

namespace {

using testing::ElementsAre;
using testing::Eq;

using memento_pattern_modern::persistent::ShapeCanvas;

TEST(ModernPersistentMemento, AddingAShapeCreatesANewCanvasVersion)
{
    const ShapeCanvas empty_canvas;
    const auto with_sun = empty_canvas.added_circle("sun", 10.0);

    EXPECT_TRUE(empty_canvas.shape_names().empty());
    EXPECT_THAT(with_sun.shape_names(), ElementsAre("sun"));
}

TEST(ModernPersistentMemento, PreviousVersionsActAsUndoPoints)
{
    const ShapeCanvas empty_canvas;
    const auto with_sun = empty_canvas.added_circle("sun", 10.0);
    const auto with_ground = with_sun.added_rectangle("ground", 100.0, 20.0);

    const ShapeCanvas undo = with_sun;

    EXPECT_THAT(with_ground.shape_names(), ElementsAre("sun", "ground"));
    EXPECT_THAT(undo.shape_names(), ElementsAre("sun"));
}

TEST(ModernPersistentMemento, VersionsCanBeStoredAsHistory)
{
    std::vector<ShapeCanvas> history;
    ShapeCanvas canvas;

    history.push_back(canvas);
    canvas = canvas.added_circle("sun", 10.0);
    history.push_back(canvas);
    canvas = canvas.added_rectangle("ground", 100.0, 20.0);

    canvas = history.back();

    EXPECT_THAT(canvas.shape_names(), ElementsAre("sun"));
}

TEST(ModernPersistentMemento, SelectionCreatesANewCanvasVersion)
{
    const ShapeCanvas canvas = ShapeCanvas{}.added_circle("sun", 10.0);
    const auto selected_canvas = canvas.selected("sun");

    EXPECT_EQ(canvas.selected_shape(), std::nullopt);
    EXPECT_THAT(selected_canvas.selected_shape(), Eq(std::optional<std::string>{"sun"}));
}

}  // namespace
