#pragma once

#include <SingletonPattern_common/SingletonBase.hpp>

#include <memory>
#include <mutex>

namespace singleton_pattern_modern::call_once {

template <typename Derived>
class CallOnceSingleton : private singleton_pattern_common::SingletonBase {
public:
    [[nodiscard]] static Derived& instance()
    {
        std::call_once(init_flag_, [] {
            instance_.reset(new Derived{});
        });

        return *instance_;
    }

protected:
    CallOnceSingleton() = default;
    ~CallOnceSingleton() = default;

private:
    inline static std::once_flag init_flag_;
    inline static std::unique_ptr<Derived> instance_{nullptr};
};

}  // namespace singleton_pattern_modern::call_once
