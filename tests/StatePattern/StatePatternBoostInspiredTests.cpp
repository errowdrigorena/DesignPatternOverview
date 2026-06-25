#include <gtest/gtest.h>
#include "StatePattern_boost_inspired/CoffeeMachine.hpp"

using CT = coffee::CoffeeType;
using CS = coffee::CupSize;
using St = bi::CMState;

TEST(BoostInspiredCoffeeMachine, StartsInReady) {
    bi::CoffeeMachineDef m;
    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_EQ(m.stateName(), "Ready");
}

TEST(BoostInspiredCoffeeMachine, HappyPath) {
    bi::CoffeeMachineDef m;
    m.selectCoffee({CT::Cappuccino, CS::Medium});
    EXPECT_EQ(m.currentState(), St::Grinding);
    EXPECT_EQ(m.order->type, CT::Cappuccino);

    m.grindDone();
    EXPECT_EQ(m.currentState(), St::Brewing);

    m.brewDone();
    EXPECT_EQ(m.currentState(), St::Dispensing);

    m.dispenseDone();
    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_FALSE(m.order.has_value());
}

TEST(BoostInspiredCoffeeMachine, CancelDuringGrinding) {
    bi::CoffeeMachineDef m;
    m.selectCoffee({CT::Americano, CS::Small});
    m.cancel();
    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_FALSE(m.order.has_value());
}

TEST(BoostInspiredCoffeeMachine, FaultAndReset) {
    bi::CoffeeMachineDef m;
    m.selectCoffee({CT::Espresso, CS::Large});
    m.grindDone();
    m.fault("Steam pressure low");
    EXPECT_EQ(m.currentState(), St::Error);
    EXPECT_EQ(m.faultReason, "Steam pressure low");

    m.reset();
    EXPECT_EQ(m.currentState(), St::Ready);
    EXPECT_TRUE(m.faultReason.empty());
}

TEST(BoostInspiredCoffeeMachine, UnknownTransitionIsIgnored) {
    bi::CoffeeMachineDef m;
    // GrindDone when Ready — no row matches, state unchanged
    m.grindDone();
    EXPECT_EQ(m.currentState(), St::Ready);
}

TEST(BoostInspiredCoffeeMachine, ProfileSetOnSelection) {
    bi::CoffeeMachineDef m;
    m.selectCoffee({CT::Latte, CS::Large});
    ASSERT_TRUE(m.profile.has_value());
    EXPECT_EQ(m.profile->grindLevel, 6);
    EXPECT_FLOAT_EQ(m.profile->waterMl, 270.f);   // 90 * 3
}
