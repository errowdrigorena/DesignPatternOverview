#pragma once

#include <ProxyPattern_modern/RealService.hpp>

#include <optional>
#include <string>

namespace proxy_pattern_modern {

// std::optional stores the subject inline — no heap allocation on lazy init.
class VirtualProxy {
public:
    explicit VirtualProxy(std::string service_id);
    [[nodiscard]] std::string request() const;
    [[nodiscard]] bool is_loaded() const noexcept;

private:
    mutable std::optional<RealService> subject_;
    std::string service_id_;
};

}  // namespace proxy_pattern_modern
