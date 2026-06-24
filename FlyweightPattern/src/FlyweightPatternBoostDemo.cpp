#include <FlyweightPattern_boost/MapOverlay.hpp>

#include <iostream>

int main()
{
    using flyweight_pattern_boost::MapOverlay;
    using flyweight_pattern_boost::MarkerStyle;

    MapOverlay overlay;
    overlay.add_marker("Central Cafe", 40.4168, -3.7038, MarkerStyle{"cafe", "red", 'C'});
    overlay.add_marker("Corner Cafe",  40.4172, -3.7041, MarkerStyle{"cafe", "red", 'C'});
    overlay.add_marker("Retiro",       40.4153, -3.6844, MarkerStyle{"park", "green", 'P'});

    overlay.draw(std::cout);

    const auto& markers = overlay.markers();
    const bool cafe_styles_shared = (markers[0].style == markers[1].style);
    const bool cafe_park_different = (markers[0].style != markers[2].style);

    std::cout << "Cafe markers share flyweight: " << std::boolalpha << cafe_styles_shared << '\n';
    std::cout << "Cafe and park are different:  " << cafe_park_different << '\n';
}
