#include <ProxyPattern_modern/ProtectionProxy.hpp>
#include <ProxyPattern_modern/VirtualProxy.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>

namespace {

using testing::HasSubstr;

TEST(ModernProxy, VirtualProxyIsNotLoadedBeforeFirstRequest)
{
    proxy_pattern_modern::VirtualProxy proxy{"test_service"};
    EXPECT_FALSE(proxy.is_loaded());
}

TEST(ModernProxy, VirtualProxyLoadsOnFirstRequest)
{
    proxy_pattern_modern::VirtualProxy proxy{"test_service"};
    static_cast<void>(proxy.request());
    EXPECT_TRUE(proxy.is_loaded());
}

TEST(ModernProxy, VirtualProxyDelegatesRequestToSubject)
{
    proxy_pattern_modern::VirtualProxy proxy{"test_service"};
    EXPECT_THAT(proxy.request(), HasSubstr("test_service"));
}

TEST(ModernProxy, VirtualProxyReusesSameSubjectOnSubsequentRequests)
{
    proxy_pattern_modern::VirtualProxy proxy{"test_service"};
    EXPECT_EQ(proxy.request(), proxy.request());
    EXPECT_TRUE(proxy.is_loaded());
}

TEST(ModernProxy, ProtectionProxyGrantsAccessWithTruePredicate)
{
    proxy_pattern_modern::ProtectionProxy proxy{"svc", [] { return true; }};
    EXPECT_THAT(proxy.request(), HasSubstr("svc"));
}

TEST(ModernProxy, ProtectionProxyDeniesAccessWithFalsePredicate)
{
    proxy_pattern_modern::ProtectionProxy proxy{"svc", [] { return false; }};
    EXPECT_THROW(static_cast<void>(proxy.request()), std::runtime_error);
}

TEST(ModernProxy, ProtectionProxyAccessPredicateIsDynamicallyCalled)
{
    bool authorized = true;
    proxy_pattern_modern::ProtectionProxy proxy{"svc", [&authorized] { return authorized; }};

    EXPECT_THAT(proxy.request(), HasSubstr("svc"));

    authorized = false;
    EXPECT_THROW(static_cast<void>(proxy.request()), std::runtime_error);

    authorized = true;
    EXPECT_THAT(proxy.request(), HasSubstr("svc"));
}

}  // namespace
