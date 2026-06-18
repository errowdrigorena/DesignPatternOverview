#pragma once

#include <iosfwd>
#include <string>
#include <string_view>

namespace flyweight_pattern_classic {

class MarkerIcon {
public:
    MarkerIcon(std::string category, std::string color, char symbol);

    [[nodiscard]] const std::string& category() const noexcept;
    [[nodiscard]] const std::string& color() const noexcept;
    [[nodiscard]] char symbol() const noexcept;

    [[nodiscard]] std::string cache_key() const;
    void draw(std::string_view label, double latitude, double longitude, std::ostream& output) const;

private:
    std::string category_;
    std::string color_;
    char symbol_{};
};

}  // namespace flyweight_pattern_classic
