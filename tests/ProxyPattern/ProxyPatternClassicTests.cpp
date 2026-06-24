#include <ProxyPattern_classic/ProtectionProxy.hpp>
#include <ProxyPattern_classic/RealService.hpp>
#include <ProxyPattern_classic/VirtualProxy.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

namespace {

using testing::HasSubstr;

TEST(ClassicProxy, VirtualProxyIsNotLoadedBeforeFirstRequest)
{
    proxy_pattern_classic::VirtualProxy proxy{"test_service"};
    EXPECT_FALSE(proxy.is_loaded());
}

TEST(ClassicProxy, VirtualProxyLoadsOnFirstRequest)
{
    proxy_pattern_classic::VirtualProxy proxy{"test_service"};
    static_cast<void>(proxy.request());
    EXPECT_TRUE(proxy.is_loaded());
}

TEST(ClassicProxy, VirtualProxyDelegatesRequestToRealService)
{
    proxy_pattern_classic::VirtualProxy proxy{"test_service"};
    EXPECT_THAT(proxy.request(), HasSubstr("test_service"));
}

TEST(ClassicProxy, VirtualProxyReusesSameServiceOnSubsequentRequests)
{
    proxy_pattern_classic::VirtualProxy proxy{"test_service"};
    EXPECT_EQ(proxy.request(), proxy.request());
    EXPECT_TRUE(proxy.is_loaded());
}

TEST(ClassicProxy, VirtualProxyIsSubstitutableForService)
{
    proxy_pattern_classic::VirtualProxy proxy{"test_service"};
    const proxy_pattern_classic::Service& as_service = proxy;
    EXPECT_THAT(as_service.request(), HasSubstr("test_service"));
}

TEST(ClassicProxy, ProtectionProxyGrantsAccessWhenAuthorized)
{
    proxy_pattern_classic::ProtectionProxy proxy{
        std::make_unique<proxy_pattern_classic::RealService>("svc"), true};
    EXPECT_THAT(proxy.request(), HasSubstr("svc"));
}

TEST(ClassicProxy, ProtectionProxyDeniesAccessWhenUnauthorized)
{
    proxy_pattern_classic::ProtectionProxy proxy{
        std::make_unique<proxy_pattern_classic::RealService>("svc"), false};
    EXPECT_THROW(static_cast<void>(proxy.request()), std::runtime_error);
}

TEST(ClassicProxy, ProtectionProxyIsSubstitutableForService)
{
    proxy_pattern_classic::ProtectionProxy proxy{
        std::make_unique<proxy_pattern_classic::RealService>("svc"), true};
    const proxy_pattern_classic::Service& as_service = proxy;
    EXPECT_THAT(as_service.request(), HasSubstr("svc"));
}

TEST(ClassicProxy, ProtectionProxyCanWrapVirtualProxy)
{
    auto virtual_proxy = std::make_unique<proxy_pattern_classic::VirtualProxy>("lazy_svc");
    proxy_pattern_classic::ProtectionProxy proxy{std::move(virtual_proxy), true};
    EXPECT_THAT(proxy.request(), HasSubstr("lazy_svc"));
}

}  // namespace
