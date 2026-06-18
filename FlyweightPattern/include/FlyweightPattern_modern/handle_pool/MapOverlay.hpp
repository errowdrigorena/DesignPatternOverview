#pragma once

#include <compare>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace flyweight_pattern_modern_handle_pool {

using StyleId = std::uint32_t;

struct MarkerStyle {
    std::string category;
    std::string color;
    char symbol{};

    [[nodiscard]] auto operator<=>(const MarkerStyle&) const = default;
};

class StyleStore {
public:
    [[nodiscard]] StyleId intern(MarkerStyle style)
    {
        if (const auto found = ids_.find(style); found != ids_.end()) {
            return found->second;
        }

        const auto id = static_cast<StyleId>(styles_.size());
        ids_.emplace(style, id);
        styles_.push_back(std::move(style));
        return id;
    }

    [[nodiscard]] const MarkerStyle& style(const StyleId id) const
    {
        if (id >= styles_.size()) {
            throw std::out_of_range{"Unknown marker style id"};
        }
        return styles_[id];
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return styles_.size();
    }

private:
    std::vector<MarkerStyle> styles_;
    std::map<MarkerStyle, StyleId> ids_;
};

struct Marker {
    std::string label;
    double latitude{};
    double longitude{};
    StyleId style{};
};

class MapOverlay {
public:
    void add_marker(std::string label, const double latitude, const double longitude, const StyleId style)
    {
        markers_.push_back(Marker{std::move(label), latitude, longitude, style});
    }

    [[nodiscard]] const std::vector<Marker>& markers() const noexcept
    {
        return markers_;
    }

    void draw(std::ostream& output, const StyleStore& styles) const
    {
        for (const auto& marker : markers_) {
            const auto& style = styles.style(marker.style);
            output << "Marker{label='" << marker.label << "', lat=" << marker.latitude
                   << ", lon=" << marker.longitude << ", icon=" << style.category
                   << '/' << style.color << '/' << style.symbol << "}\n";
        }
    }

private:
    std::vector<Marker> markers_;
};

}  // namespace flyweight_pattern_modern_handle_pool
