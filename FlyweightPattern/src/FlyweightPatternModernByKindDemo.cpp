#include <FlyweightPattern_modern/enum_kind/MapOverlay.hpp>

#include <iostream>

int main()
{
    using flyweight_pattern_modern_by_kind::MapOverlay;
    using flyweight_pattern_modern_by_kind::MarkerKind;
    using flyweight_pattern_modern_by_kind::StyleCatalog;

    StyleCatalog styles;
    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerKind::Cafe, styles);
    overlay.add_marker("Corner Cafe", 40.4172, -3.7041, MarkerKind::Cafe, styles);
    overlay.add_marker("Retiro", 40.4153, -3.6844, MarkerKind::Park, styles);

    overlay.draw(std::cout);
    std::cout << "Shared styles stored: " << styles.shared_style_count() << '\n';
}
