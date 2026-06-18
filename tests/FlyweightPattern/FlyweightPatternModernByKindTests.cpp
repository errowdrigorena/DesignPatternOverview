#include <FlyweightPattern_modern/enum_kind/MapOverlay.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace {

using flyweight_pattern_modern_by_kind::MapOverlay;
using flyweight_pattern_modern_by_kind::MarkerKind;
using flyweight_pattern_modern_by_kind::StyleCatalog;

TEST(ModernKindStyleCatalog, ReusesStylesForTheSameMarkerKind)
{
    StyleCatalog styles;

    const auto first = styles.style_for(MarkerKind::Cafe);
    const auto second = styles.style_for(MarkerKind::Cafe);
    const auto park = styles.style_for(MarkerKind::Park);

    EXPECT_EQ(first, second);
    EXPECT_NE(first, park);
    EXPECT_EQ(styles.shared_style_count(), 2U);
}

TEST(ModernKindMapOverlay, AddsMarkersByEnumKind)
{
    StyleCatalog styles;
    MapOverlay overlay;

    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerKind::Cafe, styles);
    overlay.add_marker("Corner Cafe", 40.4172, -3.7041, MarkerKind::Cafe, styles);

    ASSERT_EQ(overlay.markers().size(), 2U);
    EXPECT_EQ(overlay.markers()[0].style, overlay.markers()[1].style);
    EXPECT_EQ(overlay.markers()[0].label, "Central Cafe");
    EXPECT_DOUBLE_EQ(overlay.markers()[1].longitude, -3.7041);
}

TEST(ModernKindMapOverlay, RendersSharedStyleWithMarkerPosition)
{
    StyleCatalog styles;
    MapOverlay overlay;
    overlay.add_marker("Prado", 40.4138, -3.6921, MarkerKind::Museum, styles);
    std::ostringstream output;

    overlay.draw(output);

    EXPECT_EQ(output.str(), "Marker{label='Prado', lat=40.4138, lon=-3.6921, icon=museum/blue/M}\n");
}

}  // namespace
