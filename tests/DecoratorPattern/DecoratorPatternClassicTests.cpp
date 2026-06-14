#include <DecoratorPattern_classic/ConcreteComponent.hpp>
#include <DecoratorPattern_classic/ConcreteDecoratorA.hpp>
#include <DecoratorPattern_classic/ConcreteDecoratorB.hpp>
#include <DecoratorPattern_classic/ConcreteDecoratorC.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

namespace {

using testing::Eq;

using decorator_pattern_classic::ConcreteComponent;
using decorator_pattern_classic::ConcreteDecoratorA;
using decorator_pattern_classic::ConcreteDecoratorB;
using decorator_pattern_classic::ConcreteDecoratorC;

TEST(ClassicDecorator, ConcreteComponentWritesBaseOperation)
{
    ConcreteComponent component;

    testing::internal::CaptureStdout();
    component.operation();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, Eq("ConcreteComponent"));
}

TEST(ClassicDecorator, SingleDecoratorExtendsWrappedComponent)
{
    ConcreteDecoratorA component{std::make_unique<ConcreteComponent>()};

    testing::internal::CaptureStdout();
    component.operation();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, Eq("ConcreteComponent + DecoratorA"));
}

TEST(ClassicDecorator, StackedDecoratorsRunFromInnerToOuter)
{
    ConcreteDecoratorA component{
        std::make_unique<ConcreteDecoratorB>(
            std::make_unique<ConcreteDecoratorC>(
                std::make_unique<ConcreteComponent>()))};

    testing::internal::CaptureStdout();
    component.operation();
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, Eq("ConcreteComponent + DecoratorC + DecoratorB + DecoratorA"));
}

}  // namespace
