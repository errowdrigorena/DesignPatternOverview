#pragma once

#include <SingletonPattern_common/SingletonBase.hpp>

namespace singleton_pattern_modern::meyers {

template <typename Derived>
class MeyersSingleton : private singleton_pattern_common::SingletonBase {
public:
    [[nodiscard]] static Derived& instance()
    {
        static_assert(
            requires { Derived{}; },
            "MeyersSingleton<T> requires T to be default-constructible from the singleton base. "
            "If T needs construction arguments, use an explicit initialization policy instead.");

        static Derived instance;
        return instance;
    }

protected:
    MeyersSingleton() = default;
    ~MeyersSingleton() = default;
};

}  // namespace singleton_pattern_modern::meyers
