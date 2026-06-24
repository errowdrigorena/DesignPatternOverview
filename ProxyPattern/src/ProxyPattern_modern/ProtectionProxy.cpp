#include <ProxyPattern_modern/ProtectionProxy.hpp>

#include <stdexcept>

namespace proxy_pattern_modern {

ProtectionProxy::ProtectionProxy(std::string service_id, std::function<bool()> access_check)
    : subject_{std::move(service_id)}, access_check_{std::move(access_check)}
{}

std::string ProtectionProxy::request() const
{
    if (!access_check_()) {
        throw std::runtime_error("Access denied");
    }
    return subject_.request();
}

}  // namespace proxy_pattern_modern
