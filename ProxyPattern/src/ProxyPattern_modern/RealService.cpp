#include <ProxyPattern_modern/RealService.hpp>

namespace proxy_pattern_modern {

RealService::RealService(std::string service_id)
    : service_id_{std::move(service_id)}
{}

std::string RealService::request() const
{
    return "RealService[" + service_id_ + "]: response";
}

}  // namespace proxy_pattern_modern
