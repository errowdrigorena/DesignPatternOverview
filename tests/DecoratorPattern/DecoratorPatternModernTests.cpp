#include <DecoratorPattern_modern/ConcreteComponent.hpp>
#include <DecoratorPattern_modern/DecoratorA.hpp>
#include <DecoratorPattern_modern/DecoratorB.hpp>
#include <DecoratorPattern_modern/DecoratorC.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using testing::Eq;

using decorator_pattern_modern::ConcreteComponent;
using decorator_pattern_modern::DecoratorA;
using decorator_pattern_modern::DecoratorB;
using decorator_pattern_modern::DecoratorC;

TEST(ModernDecorator, ConcreteComponentWritesBaseOperation)
{
    ConcreteComponent component;

    testing::internal::CaptureStdout();
    component.operation();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, Eq("ConcreteComponent"));
}

TEST(ModernDecorator, SingleDecoratorExtendsBaseType)
{
    DecoratorA<ConcreteComponent> component;

    testing::internal::CaptureStdout();
    component.operation();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, Eq("ConcreteComponent + DecoratorA"));
}

TEST(ModernDecorator, StackedDecoratorsRunFromBaseToMostDerived)
{
    DecoratorA<DecoratorB<DecoratorC<ConcreteComponent>>> component;

    testing::internal::CaptureStdout();
    component.operation();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, Eq("ConcreteComponent + DecoratorC + DecoratorB + DecoratorA"));
}

}  // namespace
