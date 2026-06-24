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

TEST(ClassicDecorator, WrappingOrderDeterminesExecutionSequence)
{
    ConcreteDecoratorB b_wraps_a{std::make_unique<ConcreteDecoratorA>(std::make_unique<ConcreteComponent>())};
    ConcreteDecoratorA a_wraps_b{std::make_unique<ConcreteDecoratorB>(std::make_unique<ConcreteComponent>())};

    testing::internal::CaptureStdout();
    b_wraps_a.operation();
    const auto b_over_a = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    a_wraps_b.operation();
    const auto a_over_b = testing::internal::GetCapturedStdout();

    EXPECT_THAT(b_over_a, Eq("ConcreteComponent + DecoratorA + DecoratorB"));
    EXPECT_THAT(a_over_b, Eq("ConcreteComponent + DecoratorB + DecoratorA"));
}

}  // namespace
