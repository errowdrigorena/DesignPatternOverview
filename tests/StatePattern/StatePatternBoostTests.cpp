#include <gtest/gtest.h>
#include "StatePattern_boost/CoffeeMachine.hpp"

using CT = coffee::CoffeeType;
using CS = coffee::CupSize;

TEST(BoostMsmCoffeeMachine, StartsInReady) {
    bmsm::CoffeeMachine m;
    EXPECT_EQ(m.stateName(), "Ready");
}

TEST(BoostMsmCoffeeMachine, HappyPath) {
    bmsm::CoffeeMachine m;
    m.selectCoffee({CT::Espresso, CS::Small});
    EXPECT_EQ(m.stateName(), "Grinding");
    EXPECT_EQ(m.order()->type, CT::Espresso);

    m.grindDone();
    EXPECT_EQ(m.stateName(), "Brewing");

    m.brewDone();
    EXPECT_EQ(m.stateName(), "Dispensing");

    m.dispenseDone();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.hasOrder());
}

TEST(BoostMsmCoffeeMachine, CancelDuringGrinding) {
    bmsm::CoffeeMachine m;
    m.selectCoffee({CT::Latte, CS::Medium});
    m.cancel();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.hasOrder());
}

TEST(BoostMsmCoffeeMachine, FaultAndReset) {
    bmsm::CoffeeMachine m;
    m.selectCoffee({CT::Americano, CS::Large});
    m.grindDone();
    m.fault("Water level low");
    EXPECT_EQ(m.stateName(), "Error");
    EXPECT_EQ(m.faultReason(), "Water level low");

    m.reset();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_TRUE(m.faultReason().empty());
}

TEST(BoostMsmCoffeeMachine, ProfileSetCorrectly) {
    bmsm::CoffeeMachine m;
    m.selectCoffee({CT::Cappuccino, CS::Small});
    ASSERT_TRUE(m.profile().has_value());
    EXPECT_EQ(m.profile()->grindLevel, 7);
    EXPECT_FLOAT_EQ(m.profile()->waterMl, 60.f);  // 30 * 2
}
