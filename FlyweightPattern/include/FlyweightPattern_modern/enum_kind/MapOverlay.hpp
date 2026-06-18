#pragma once

#include <array>
#include <cstddef>
#include <iosfwd>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace flyweight_pattern_modern_by_kind {

enum class MarkerKind {
    Cafe,
    Park,
    Museum,
};

struct MarkerStyle {
    std::string category;
    std::string color;
    char symbol{};
};

class StyleCatalog {
public:
    [[nodiscard]] std::shared_ptr<const MarkerStyle> style_for(const MarkerKind kind)
    {
        auto& style = styles_[index_of(kind)];
        if (!style) {
            style = std::make_shared<MarkerStyle>(make_style(kind));
        }
        return style;
    }

    [[nodiscard]] std::size_t shared_style_count() const noexcept
    {
        std::size_t count{};
        for (const auto& style : styles_) {
            if (style) {
                ++count;
            }
        }
        return count;
    }

private:
    static constexpr std::size_t index_of(const MarkerKind kind) noexcept
    {
        return static_cast<std::size_t>(kind);
    }

    static MarkerStyle make_style(const MarkerKind kind)
    {
        switch (kind) {
            case MarkerKind::Cafe:
                return MarkerStyle{"cafe", "red", 'C'};
            case MarkerKind::Park:
                return MarkerStyle{"park", "green", 'P'};
            case MarkerKind::Museum:
                return MarkerStyle{"museum", "blue", 'M'};
        }

        return MarkerStyle{"unknown", "gray", '?'};
    }

    std::array<std::shared_ptr<const MarkerStyle>, 3> styles_{};
};

struct Marker {
    std::string label;
    double latitude{};
    double longitude{};
    std::shared_ptr<const MarkerStyle> style;
};

class MapOverlay {
public:
    void add_marker(
        std::string label,
        const double latitude,
        const double longitude,
        const MarkerKind kind,
        StyleCatalog& styles)
    {
        markers_.push_back(Marker{std::move(label), latitude, longitude, styles.style_for(kind)});
    }

    [[nodiscard]] const std::vector<Marker>& markers() const noexcept
    {
        return markers_;
    }

    void draw(std::ostream& output) const
    {
        for (const auto& marker : markers_) {
            output << "Marker{label='" << marker.label << "', lat=" << marker.latitude
                   << ", lon=" << marker.longitude << ", icon=" << marker.style->category
                   << '/' << marker.style->color << '/' << marker.style->symbol << "}\n";
        }
    }

private:
    std::vector<Marker> markers_;
};

}  // namespace flyweight_pattern_modern_by_kind
