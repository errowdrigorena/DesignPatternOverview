#pragma once

#include <FlyweightPattern_classic/MarkerIcon.hpp>

#include <cstddef>
#include <map>
#include <memory>
#include <string>

namespace flyweight_pattern_classic {

class IconCatalog {
public:
    [[nodiscard]] std::shared_ptr<const MarkerIcon> icon_for(
        std::string category,
        std::string color,
        char symbol);

    [[nodiscard]] std::size_t shared_icon_count() const noexcept;

private:
    std::map<std::string, std::shared_ptr<const MarkerIcon>> icons_;
};

}  // namespace flyweight_pattern_classic
