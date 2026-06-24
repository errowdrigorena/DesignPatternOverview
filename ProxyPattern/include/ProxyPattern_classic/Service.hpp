#pragma once

#include <string>

namespace proxy_pattern_classic {

class Service {
public:
    virtual ~Service() = default;
    [[nodiscard]] virtual std::string request() const = 0;
};

}  // namespace proxy_pattern_classic
