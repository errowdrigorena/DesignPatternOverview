#include <FlyweightPattern_classic/MarkerIcon.hpp>

#include <ostream>
#include <sstream>
#include <string_view>
#include <utility>

namespace flyweight_pattern_classic {

MarkerIcon::MarkerIcon(std::string category, std::string color, const char symbol)
    : category_{std::move(category)}
    , color_{std::move(color)}
    , symbol_{symbol}
{
}

const std::string& MarkerIcon::category() const noexcept
{
    return category_;
}

const std::string& MarkerIcon::color() const noexcept
{
    return color_;
}

char MarkerIcon::symbol() const noexcept
{
    return symbol_;
}

std::string MarkerIcon::cache_key() const
{
    std::ostringstream key;
    key << category_ << '|' << color_ << '|' << symbol_;
    return key.str();
}

void MarkerIcon::draw(const std::string_view label, const double latitude, const double longitude, std::ostream& output)
    const
{
    output << "Marker{label='" << label << "', lat=" << latitude << ", lon=" << longitude
           << ", icon=" << category_ << '/' << color_ << '/' << symbol_ << "}\n";
}

}  // namespace flyweight_pattern_classic
