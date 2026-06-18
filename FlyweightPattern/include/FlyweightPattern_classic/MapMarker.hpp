#pragma once

#include <FlyweightPattern_classic/MarkerIcon.hpp>

#include <iosfwd>
#include <memory>
#include <string>

namespace flyweight_pattern_classic {

class MapMarker {
public:
    MapMarker(std::string label, double latitude, double longitude, std::shared_ptr<const MarkerIcon> icon);

    void draw(std::ostream& output) const;

    [[nodiscard]] const std::string& label() const noexcept;
    [[nodiscard]] double latitude() const noexcept;
    [[nodiscard]] double longitude() const noexcept;
    [[nodiscard]] std::shared_ptr<const MarkerIcon> icon() const noexcept;

private:
    std::string label_;
    double latitude_{};
    double longitude_{};
    std::shared_ptr<const MarkerIcon> icon_;
};

}  // namespace flyweight_pattern_classic
