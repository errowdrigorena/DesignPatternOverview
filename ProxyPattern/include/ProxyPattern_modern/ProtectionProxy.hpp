#pragma once

#include <ProxyPattern_modern/RealService.hpp>

#include <functional>
#include <string>

namespace proxy_pattern_modern {

// std::function<bool()> as access predicate — composable and captureable.
class ProtectionProxy {
public:
    ProtectionProxy(std::string service_id, std::function<bool()> access_check);
    [[nodiscard]] std::string request() const;

private:
    RealService subject_;
    std::function<bool()> access_check_;
};

}  // namespace proxy_pattern_modern
