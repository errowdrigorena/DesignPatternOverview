#include <FlyweightPattern_modern/value_pool/MapOverlay.hpp>

#include <iostream>

int main()
{
    using flyweight_pattern_modern::MapOverlay;
    using flyweight_pattern_modern::MarkerStyle;
    using flyweight_pattern_modern::StylePool;

    StylePool styles;
    const auto cafe = styles.share(MarkerStyle{"cafe", "red", 'C'});
    const auto park = styles.share(MarkerStyle{"park", "green", 'P'});

    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, cafe);
    overlay.add_marker("Corner Cafe", 40.4172, -3.7041, cafe);
    overlay.add_marker("Retiro", 40.4153, -3.6844, park);

    overlay.draw(std::cout);
    std::cout << "Shared styles stored: " << styles.size() << '\n';
}
