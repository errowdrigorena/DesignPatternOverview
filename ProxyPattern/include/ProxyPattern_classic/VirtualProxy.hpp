#pragma once

#include <ProxyPattern_classic/RealService.hpp>
#include <ProxyPattern_classic/Service.hpp>

#include <memory>
#include <string>

namespace proxy_pattern_classic {

class VirtualProxy final : public Service {
public:
    explicit VirtualProxy(std::string service_id);
    [[nodiscard]] std::string request() const override;
    [[nodiscard]] bool is_loaded() const noexcept;

private:
    mutable std::unique_ptr<RealService> real_service_;
    std::string service_id_;
};

}  // namespace proxy_pattern_classic
