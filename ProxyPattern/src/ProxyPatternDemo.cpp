#include <ProxyPattern_classic/ProtectionProxy.hpp>
#include <ProxyPattern_classic/RealService.hpp>
#include <ProxyPattern_classic/VirtualProxy.hpp>

#include <iostream>
#include <memory>

int main()
{
    using namespace proxy_pattern_classic;

    VirtualProxy virtual_proxy{"database_service"};
    std::cout << "VirtualProxy created, service not yet loaded.\n";
    std::cout << virtual_proxy.request() << '\n';
    std::cout << virtual_proxy.request() << '\n';

    ProtectionProxy authorized{std::make_unique<RealService>("secure_service"), true};
    std::cout << authorized.request() << '\n';

    ProtectionProxy unauthorized{std::make_unique<RealService>("secure_service"), false};
    try {
        std::cout << unauthorized.request() << '\n';
    } catch (const std::runtime_error& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
}
