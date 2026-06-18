#include <FlyweightPattern_modern/static_table/MapOverlay.hpp>

#include <iostream>

int main()
{
    using flyweight_pattern_modern_static_table::MapOverlay;
    using flyweight_pattern_modern_static_table::MarkerKind;
    using flyweight_pattern_modern_static_table::marker_styles;

    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerKind::Cafe);
    overlay.add_marker("Corner Cafe", 40.4172, -3.7041, MarkerKind::Cafe);
    overlay.add_marker("Retiro", 40.4153, -3.6844, MarkerKind::Park);

    overlay.draw(std::cout);
    std::cout << "Shared styles stored: " << marker_styles.size() << '\n';
}
