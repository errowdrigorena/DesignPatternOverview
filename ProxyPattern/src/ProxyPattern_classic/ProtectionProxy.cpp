#include <ProxyPattern_classic/ProtectionProxy.hpp>

#include <stdexcept>

namespace proxy_pattern_classic {

ProtectionProxy::ProtectionProxy(std::unique_ptr<Service> service, bool authorized)
    : service_{std::move(service)}, authorized_{authorized}
{}

std::string ProtectionProxy::request() const
{
    if (!authorized_) {
        throw std::runtime_error("Access denied");
    }
    return service_->request();
}

}  // namespace proxy_pattern_classic
