#pragma once

namespace singleton_pattern_common {

class SingletonBase {
public:
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
    SingletonBase(SingletonBase&&) = delete;
    SingletonBase& operator=(SingletonBase&&) = delete;

protected:
    SingletonBase() = default;
    ~SingletonBase() = default;
};

}  // namespace singleton_pattern_common
