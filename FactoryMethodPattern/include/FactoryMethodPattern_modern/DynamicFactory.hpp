#pragma once

#include <concepts>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace factory_method_pattern_modern {

template <typename Creator, typename Product, typename... Args>
concept ProductCreator =
    std::regular_invocable<const Creator&, Args...>
    && std::convertible_to<
        std::invoke_result_t<const Creator&, Args...>,
        std::unique_ptr<Product>>;

template <
    typename Product,
    typename Key,
    typename Creator = std::unique_ptr<Product> (*)()>
class DynamicFactory {
public:
    void register_creator(Key key, Creator creator)
    {
        creators_.insert_or_assign(std::move(key), std::move(creator));
    }

    [[nodiscard]] bool unregister_creator(const Key& key)
    {
        return creators_.erase(key) == 1;
    }

    template <typename... Args>
    [[nodiscard]] decltype(auto) create(const Key& key, Args&&... args) const
        requires ProductCreator<Creator, Product, Args...>
    {
        const auto creator = creators_.find(key);
        if (creator == creators_.end()) {
            throw std::out_of_range{"DynamicFactory: key not registered"};
        }

        return creator->second(std::forward<Args>(args)...);
    }

    [[nodiscard]] bool empty() const
    {
        return creators_.empty();
    }

private:
    std::unordered_map<Key, Creator> creators_;
};

}  // namespace factory_method_pattern_modern
