#pragma once

#include <compare>
#include <cstddef>
#include <iosfwd>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace flyweight_pattern_modern {

struct MarkerStyle {
    std::string category;
    std::string color;
    char symbol{};

    [[nodiscard]] auto operator<=>(const MarkerStyle&) const = default;
};

class StylePool {
public:
    [[nodiscard]] std::shared_ptr<const MarkerStyle> share(MarkerStyle style)
    {
        if (const auto found = styles_.find(style); found != styles_.end()) {
            return found->second;
        }

        auto shared_style = std::make_shared<MarkerStyle>(std::move(style));
        const auto [inserted, _] = styles_.emplace(*shared_style, shared_style);
        return inserted->second;
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return styles_.size();
    }

private:
    std::map<MarkerStyle, std::shared_ptr<const MarkerStyle>> styles_;
};

struct Marker {
    std::string label;
    double latitude{};
    double longitude{};
    std::shared_ptr<const MarkerStyle> style;
};

class MapOverlay {
public:
    void add_marker(std::string label, double latitude, double longitude, std::shared_ptr<const MarkerStyle> style)
    {
        markers_.push_back(Marker{std::move(label), latitude, longitude, std::move(style)});
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

}  // namespace flyweight_pattern_modern
