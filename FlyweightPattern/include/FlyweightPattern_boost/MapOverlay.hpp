#pragma once

#include <boost/container_hash/hash.hpp>
#include <boost/flyweight.hpp>

#include <iosfwd>
#include <ostream>
#include <string>
#include <vector>

namespace flyweight_pattern_boost {

struct MarkerStyle {
    std::string category;
    std::string color;
    char symbol{};

    [[nodiscard]] bool operator==(const MarkerStyle&) const = default;
};

inline std::ostream& operator<<(std::ostream& os, const MarkerStyle& s)
{
    return os << s.category << '/' << s.color << '/' << s.symbol;
}

// boost::flyweight uses boost::hash<T> by default, which in turn calls
// hash_value() found via ADL — so we define it here in the same namespace.
inline std::size_t hash_value(const MarkerStyle& s)
{
    std::size_t seed = 0;
    boost::hash_combine(seed, s.category);
    boost::hash_combine(seed, s.color);
    boost::hash_combine(seed, s.symbol);
    return seed;
}

struct Marker {
    std::string label;
    double latitude{};
    double longitude{};
    boost::flyweight<MarkerStyle> style;
};

class MapOverlay {
public:
    void add_marker(std::string label, double latitude, double longitude, MarkerStyle style);

    [[nodiscard]] const std::vector<Marker>& markers() const noexcept;

    void draw(std::ostream& output) const;

private:
    std::vector<Marker> markers_;
};

}  // namespace flyweight_pattern_boost
