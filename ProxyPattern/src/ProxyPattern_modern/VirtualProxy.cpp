#include <ProxyPattern_modern/VirtualProxy.hpp>

namespace proxy_pattern_modern {

VirtualProxy::VirtualProxy(std::string service_id)
    : service_id_{std::move(service_id)}
{}

std::string VirtualProxy::request() const
{
    if (!subject_) {
        subject_.emplace(service_id_);
    }
    return subject_->request();
}

bool VirtualProxy::is_loaded() const noexcept
{
    return subject_.has_value();
}

}  // namespace proxy_pattern_modern
