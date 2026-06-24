#include <FlyweightPattern_boost/MapOverlay.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace {

using flyweight_pattern_boost::MapOverlay;
using flyweight_pattern_boost::MarkerStyle;

TEST(BoostFlyweight, EqualStylesShareTheSameFlyweight)
{
    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerStyle{"cafe", "red", 'C'});
    overlay.add_marker("Corner Cafe",  40.4172, -3.7041, MarkerStyle{"cafe", "red", 'C'});
    overlay.add_marker("Retiro",       40.4153, -3.6844, MarkerStyle{"park", "green", 'P'});

    const auto& markers = overlay.markers();

    EXPECT_EQ(markers[0].style, markers[1].style);
    EXPECT_NE(markers[0].style, markers[2].style);
}

TEST(BoostFlyweight, FlyweightAddressIsTheSameForEqualValues)
{
    MapOverlay overlay;
    overlay.add_marker("A", 0.0, 0.0, MarkerStyle{"cafe", "red", 'C'});
    overlay.add_marker("B", 1.0, 1.0, MarkerStyle{"cafe", "red", 'C'});

    const auto& markers = overlay.markers();

    EXPECT_EQ(&markers[0].style.get(), &markers[1].style.get());
}

TEST(BoostFlyweight, DrawRendersIntrinsicAndExtrinsicState)
{
    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerStyle{"cafe", "red", 'C'});
    std::ostringstream output;

    overlay.draw(output);

    EXPECT_EQ(
        output.str(),
        "Marker{label='Central Cafe', lat=40.4168, lon=-3.7038, icon=cafe/red/C}\n");
}

TEST(BoostFlyweight, StoresExtrinsicDataPerMarker)
{
    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerStyle{"cafe", "red", 'C'});
    overlay.add_marker("Corner Cafe",  40.4172, -3.7041, MarkerStyle{"cafe", "red", 'C'});

    ASSERT_EQ(overlay.markers().size(), 2U);
    EXPECT_EQ(overlay.markers()[0].label, "Central Cafe");
    EXPECT_DOUBLE_EQ(overlay.markers()[1].longitude, -3.7041);
}

}  // namespace
