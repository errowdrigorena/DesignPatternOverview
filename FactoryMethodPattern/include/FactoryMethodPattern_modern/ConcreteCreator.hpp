#pragma once

#include <concepts>
#include <memory>
#include <type_traits>
#include <utility>

namespace factory_method_pattern_modern {

template <typename Base, std::derived_from<Base> Derived, typename... Args>
class ConcreteCreator {
public:
    [[nodiscard]] std::unique_ptr<Base> create(Args&&... args) const
        noexcept(std::is_nothrow_constructible_v<Derived, Args&&...>)
        requires std::constructible_from<Derived, Args&&...>
    {
        return std::make_unique<Derived>(std::forward<Args>(args)...);
    }
};

}  // namespace factory_method_pattern_modern
