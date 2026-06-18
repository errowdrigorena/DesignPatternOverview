#include <FlyweightPattern_modern/handle_pool/MapOverlay.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

namespace {

using flyweight_pattern_modern_handle_pool::MapOverlay;
using flyweight_pattern_modern_handle_pool::MarkerStyle;
using flyweight_pattern_modern_handle_pool::StyleStore;

TEST(ModernHandleStyleStore, ReusesIdsForEqualStyles)
{
    StyleStore styles;

    const auto first = styles.intern(MarkerStyle{"cafe", "red", 'C'});
    const auto second = styles.intern(MarkerStyle{"cafe", "red", 'C'});
    const auto park = styles.intern(MarkerStyle{"park", "green", 'P'});

    EXPECT_EQ(first, second);
    EXPECT_NE(first, park);
    EXPECT_EQ(styles.size(), 2U);
}

TEST(ModernHandleMapOverlay, StoresOnlyStyleIdsInMarkers)
{
    StyleStore styles;
    const auto cafe = styles.intern(MarkerStyle{"cafe", "red", 'C'});
    MapOverlay overlay;

    overlay.add_marker("Central Cafe", 40.4168, -3.7038, cafe);
    overlay.add_marker("Corner Cafe", 40.4172, -3.7041, cafe);

    ASSERT_EQ(overlay.markers().size(), 2U);
    EXPECT_EQ(overlay.markers()[0].style, overlay.markers()[1].style);
    EXPECT_EQ(overlay.markers()[0].label, "Central Cafe");
    EXPECT_DOUBLE_EQ(overlay.markers()[1].longitude, -3.7041);
}

TEST(ModernHandleMapOverlay, RendersByResolvingStyleIdsThroughStore)
{
    StyleStore styles;
    const auto museum = styles.intern(MarkerStyle{"museum", "blue", 'M'});
    MapOverlay overlay;
    overlay.add_marker("Prado", 40.4138, -3.6921, museum);
    std::ostringstream output;

    overlay.draw(output, styles);

    EXPECT_EQ(output.str(), "Marker{label='Prado', lat=40.4138, lon=-3.6921, icon=museum/blue/M}\n");
}

TEST(ModernHandleStyleStore, RejectsUnknownStyleIds)
{
    const StyleStore styles;

    EXPECT_THROW(static_cast<void>(styles.style(42)), std::out_of_range);
}

}  // namespace
