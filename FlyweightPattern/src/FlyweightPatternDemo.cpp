#include <FlyweightPattern_classic/IconCatalog.hpp>
#include <FlyweightPattern_classic/MapMarker.hpp>

#include <iostream>
#include <vector>

int main()
{
    using flyweight_pattern_classic::IconCatalog;
    using flyweight_pattern_classic::MapMarker;

    IconCatalog catalog;
    const auto cafe = catalog.icon_for("cafe", "red", 'C');
    const auto park = catalog.icon_for("park", "green", 'P');

    const std::vector<MapMarker> markers{
        {"Central Cafe", 40.4168, -3.7038, cafe},
        {"Corner Cafe", 40.4172, -3.7041, cafe},
        {"Retiro", 40.4153, -3.6844, park},
    };

    for (const auto& marker : markers) {
        marker.draw(std::cout);
    }

    std::cout << "Shared icons stored: " << catalog.shared_icon_count() << '\n';
}
