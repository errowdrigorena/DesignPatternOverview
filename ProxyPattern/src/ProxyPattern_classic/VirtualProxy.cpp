#include <ProxyPattern_classic/VirtualProxy.hpp>

namespace proxy_pattern_classic {

VirtualProxy::VirtualProxy(std::string service_id)
    : service_id_{std::move(service_id)}
{}

std::string VirtualProxy::request() const
{
    if (!real_service_) {
        real_service_ = std::make_unique<RealService>(service_id_);
    }
    return real_service_->request();
}

bool VirtualProxy::is_loaded() const noexcept
{
    return real_service_ != nullptr;
}

}  // namespace proxy_pattern_classic
