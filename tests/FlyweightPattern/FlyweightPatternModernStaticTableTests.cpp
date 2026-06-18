#include <FlyweightPattern_modern/static_table/MapOverlay.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace {

using flyweight_pattern_modern_static_table::MapOverlay;
using flyweight_pattern_modern_static_table::MarkerKind;
using flyweight_pattern_modern_static_table::marker_styles;
using flyweight_pattern_modern_static_table::style_for;

TEST(ModernStaticTable, ExposesSharedCompileTimeStyles)
{
    static_assert(marker_styles.size() == 3U);

    const auto& cafe = style_for(MarkerKind::Cafe);
    const auto& second_cafe = style_for(MarkerKind::Cafe);
    const auto& park = style_for(MarkerKind::Park);

    EXPECT_EQ(&cafe, &second_cafe);
    EXPECT_NE(&cafe, &park);
    EXPECT_EQ(cafe.category, "cafe");
    EXPECT_EQ(cafe.color, "red");
    EXPECT_EQ(cafe.symbol, 'C');
}

TEST(ModernStaticTableMapOverlay, StoresOnlyMarkerKindInMarkers)
{
    MapOverlay overlay;

    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerKind::Cafe);
    overlay.add_marker("Corner Cafe", 40.4172, -3.7041, MarkerKind::Cafe);

    ASSERT_EQ(overlay.markers().size(), 2U);
    EXPECT_EQ(overlay.markers()[0].kind, overlay.markers()[1].kind);
    EXPECT_EQ(overlay.markers()[0].label, "Central Cafe");
    EXPECT_DOUBLE_EQ(overlay.markers()[1].longitude, -3.7041);
}

TEST(ModernStaticTableMapOverlay, RendersByLookingUpSharedStaticStyle)
{
    MapOverlay overlay;
    overlay.add_marker("Prado", 40.4138, -3.6921, MarkerKind::Museum);
    std::ostringstream output;

    overlay.draw(output);

    EXPECT_EQ(output.str(), "Marker{label='Prado', lat=40.4138, lon=-3.6921, icon=museum/blue/M}\n");
}

}  // namespace
