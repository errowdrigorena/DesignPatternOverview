#include <FlyweightPattern_boost/MapOverlay.hpp>

#include <ostream>
#include <utility>

namespace flyweight_pattern_boost {

void MapOverlay::add_marker(std::string label, double latitude, double longitude, MarkerStyle style)
{
    markers_.push_back(Marker{std::move(label), latitude, longitude, boost::flyweight<MarkerStyle>{std::move(style)}});
}

const std::vector<Marker>& MapOverlay::markers() const noexcept
{
    return markers_;
}

void MapOverlay::draw(std::ostream& output) const
{
    for (const auto& marker : markers_) {
        const MarkerStyle& s = marker.style.get();
        output << "Marker{label='" << marker.label << "', lat=" << marker.latitude
               << ", lon=" << marker.longitude << ", icon=" << s.category
               << '/' << s.color << '/' << s.symbol << "}\n";
    }
}

}  // namespace flyweight_pattern_boost
