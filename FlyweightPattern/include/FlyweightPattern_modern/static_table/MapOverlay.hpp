#pragma once

#include <array>
#include <cstddef>
#include <iosfwd>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace flyweight_pattern_modern_static_table {

enum class MarkerKind {
    Cafe,
    Park,
    Museum,
};

struct MarkerStyle {
    std::string_view category;
    std::string_view color;
    char symbol{};
};

inline constexpr std::array marker_styles{
    MarkerStyle{"cafe", "red", 'C'},
    MarkerStyle{"park", "green", 'P'},
    MarkerStyle{"museum", "blue", 'M'},
};

[[nodiscard]] constexpr const MarkerStyle& style_for(const MarkerKind kind) noexcept
{
    return marker_styles[static_cast<std::size_t>(kind)];
}

struct Marker {
    std::string label;
    double latitude{};
    double longitude{};
    MarkerKind kind{};
};

class MapOverlay {
public:
    void add_marker(std::string label, const double latitude, const double longitude, const MarkerKind kind)
    {
        markers_.push_back(Marker{std::move(label), latitude, longitude, kind});
    }

    [[nodiscard]] const std::vector<Marker>& markers() const noexcept
    {
        return markers_;
    }

    void draw(std::ostream& output) const
    {
        for (const auto& marker : markers_) {
            const auto& style = style_for(marker.kind);
            output << "Marker{label='" << marker.label << "', lat=" << marker.latitude
                   << ", lon=" << marker.longitude << ", icon=" << style.category
                   << '/' << style.color << '/' << style.symbol << "}\n";
        }
    }

private:
    std::vector<Marker> markers_;
};

}  // namespace flyweight_pattern_modern_static_table
