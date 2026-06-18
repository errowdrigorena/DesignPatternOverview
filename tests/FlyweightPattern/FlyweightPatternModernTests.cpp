#include <FlyweightPattern_modern/value_pool/MapOverlay.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace {

using flyweight_pattern_modern::MapOverlay;
using flyweight_pattern_modern::MarkerStyle;
using flyweight_pattern_modern::StylePool;

TEST(ModernStylePool, ReusesEqualStyleValues)
{
    StylePool styles;

    const auto first = styles.share(MarkerStyle{"cafe", "red", 'C'});
    const auto second = styles.share(MarkerStyle{"cafe", "red", 'C'});
    const auto park = styles.share(MarkerStyle{"park", "green", 'P'});

    EXPECT_EQ(first, second);
    EXPECT_NE(first, park);
    EXPECT_EQ(styles.size(), 2U);
}

TEST(ModernMapOverlay, StoresExtrinsicMarkerDataWithSharedStyle)
{
    StylePool styles;
    const auto cafe = styles.share(MarkerStyle{"cafe", "red", 'C'});
    MapOverlay overlay;

    overlay.add_marker("Central Cafe", 40.4168, -3.7038, cafe);
    overlay.add_marker("Corner Cafe", 40.4172, -3.7041, cafe);

    ASSERT_EQ(overlay.markers().size(), 2U);
    EXPECT_EQ(overlay.markers()[0].style, overlay.markers()[1].style);
    EXPECT_EQ(overlay.markers()[0].label, "Central Cafe");
    EXPECT_DOUBLE_EQ(overlay.markers()[1].longitude, -3.7041);
}

TEST(ModernMapOverlay, RendersSharedIntrinsicStyleWithEachMarkerPosition)
{
    StylePool styles;
    const auto cafe = styles.share(MarkerStyle{"cafe", "red", 'C'});
    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, cafe);
    std::ostringstream output;

    overlay.draw(output);

    EXPECT_EQ(
        output.str(),
        "Marker{label='Central Cafe', lat=40.4168, lon=-3.7038, icon=cafe/red/C}\n");
}

}  // namespace
