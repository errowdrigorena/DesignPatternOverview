#include <FlyweightPattern_classic/MapMarker.hpp>

#include <stdexcept>
#include <utility>

namespace flyweight_pattern_classic {

MapMarker::MapMarker(
    std::string label,
    const double latitude,
    const double longitude,
    std::shared_ptr<const MarkerIcon> icon)
    : label_{std::move(label)}
    , latitude_{latitude}
    , longitude_{longitude}
    , icon_{std::move(icon)}
{
    if (!icon_) {
        throw std::invalid_argument{"MapMarker requires a shared marker icon"};
    }
}

void MapMarker::draw(std::ostream& output) const
{
    icon_->draw(label_, latitude_, longitude_, output);
}

const std::string& MapMarker::label() const noexcept
{
    return label_;
}

double MapMarker::latitude() const noexcept
{
    return latitude_;
}

double MapMarker::longitude() const noexcept
{
    return longitude_;
}

std::shared_ptr<const MarkerIcon> MapMarker::icon() const noexcept
{
    return icon_;
}

}  // namespace flyweight_pattern_classic
