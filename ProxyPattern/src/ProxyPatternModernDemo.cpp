#include <ProxyPattern_modern/ProtectionProxy.hpp>
#include <ProxyPattern_modern/VirtualProxy.hpp>

#include <iostream>

int main()
{
    using namespace proxy_pattern_modern;

    VirtualProxy virtual_proxy{"database_service"};
    std::cout << "VirtualProxy created, service not yet loaded.\n";
    std::cout << virtual_proxy.request() << '\n';
    std::cout << virtual_proxy.request() << '\n';

    bool is_admin = true;
    ProtectionProxy admin_proxy{"admin_service", [&is_admin] { return is_admin; }};
    std::cout << admin_proxy.request() << '\n';

    is_admin = false;
    try {
        std::cout << admin_proxy.request() << '\n';
    } catch (const std::runtime_error& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
}
