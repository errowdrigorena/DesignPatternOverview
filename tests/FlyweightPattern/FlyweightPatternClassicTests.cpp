#include <FlyweightPattern_classic/IconCatalog.hpp>
#include <FlyweightPattern_classic/MapMarker.hpp>
#include <FlyweightPattern_classic/MarkerIcon.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

namespace {

using flyweight_pattern_classic::IconCatalog;
using flyweight_pattern_classic::MapMarker;
using flyweight_pattern_classic::MarkerIcon;

TEST(ClassicMarkerIcon, BuildsStableCacheKeyFromIntrinsicState)
{
    const MarkerIcon cafe{"cafe", "red", 'C'};
    const MarkerIcon park{"park", "green", 'P'};

    EXPECT_EQ(cafe.cache_key(), "cafe|red|C");
    EXPECT_EQ(park.cache_key(), "park|green|P");
}

TEST(ClassicIconCatalog, ReusesIconsWithTheSameIntrinsicState)
{
    IconCatalog catalog;

    const auto first = catalog.icon_for("cafe", "red", 'C');
    const auto second = catalog.icon_for("cafe", "red", 'C');
    const auto park = catalog.icon_for("park", "green", 'P');

    EXPECT_EQ(first, second);
    EXPECT_NE(first, park);
    EXPECT_EQ(catalog.shared_icon_count(), 2U);
}

TEST(ClassicMapMarker, KeepsExtrinsicStateOutsideTheSharedIcon)
{
    IconCatalog catalog;
    const auto cafe = catalog.icon_for("cafe", "red", 'C');

    const MapMarker first{"Central Cafe", 40.4168, -3.7038, cafe};
    const MapMarker second{"Corner Cafe", 40.4172, -3.7041, cafe};

    EXPECT_EQ(first.icon(), second.icon());
    EXPECT_EQ(first.label(), "Central Cafe");
    EXPECT_EQ(second.label(), "Corner Cafe");
    EXPECT_DOUBLE_EQ(second.latitude(), 40.4172);
    EXPECT_DOUBLE_EQ(second.longitude(), -3.7041);
}

TEST(ClassicMapMarker, RendersExtrinsicAndIntrinsicStateTogether)
{
    IconCatalog catalog;
    const MapMarker marker{"Central Cafe", 40.4168, -3.7038, catalog.icon_for("cafe", "red", 'C')};
    std::ostringstream output;

    marker.draw(output);

    EXPECT_EQ(
        output.str(),
        "Marker{label='Central Cafe', lat=40.4168, lon=-3.7038, icon=cafe/red/C}\n");
}

TEST(ClassicMapMarker, RejectsMissingSharedIcon)
{
    EXPECT_THROW(MapMarker("Central Cafe", 40.4168, -3.7038, nullptr), std::invalid_argument);
}

}  // namespace
