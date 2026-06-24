#pragma once

#include <ProxyPattern_classic/Service.hpp>

#include <string>

namespace proxy_pattern_classic {

class RealService final : public Service {
public:
    explicit RealService(std::string service_id);
    [[nodiscard]] std::string request() const override;

private:
    std::string service_id_;
};

}  // namespace proxy_pattern_classic
