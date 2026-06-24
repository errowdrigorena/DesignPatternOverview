#pragma once

#include <ProxyPattern_classic/Service.hpp>

#include <memory>

namespace proxy_pattern_classic {

class ProtectionProxy final : public Service {
public:
    ProtectionProxy(std::unique_ptr<Service> service, bool authorized);
    [[nodiscard]] std::string request() const override;

private:
    std::unique_ptr<Service> service_;
    bool authorized_;
};

}  // namespace proxy_pattern_classic
