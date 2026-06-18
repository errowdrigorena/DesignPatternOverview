#include <FlyweightPattern_classic/IconCatalog.hpp>

#include <utility>

namespace flyweight_pattern_classic {

std::shared_ptr<const MarkerIcon> IconCatalog::icon_for(std::string category, std::string color, const char symbol)
{
    auto icon = std::make_shared<MarkerIcon>(std::move(category), std::move(color), symbol);
    const std::string key = icon->cache_key();

    if (const auto found = icons_.find(key); found != icons_.end()) {
        return found->second;
    }

    const auto [inserted, _] = icons_.emplace(key, std::move(icon));
    return inserted->second;
}

std::size_t IconCatalog::shared_icon_count() const noexcept
{
    return icons_.size();
}

}  // namespace flyweight_pattern_classic
