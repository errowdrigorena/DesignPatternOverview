#include <gtest/gtest.h>
#include "StatePattern_classic_generic/CoffeeMachine.hpp"
#include "StatePattern_classic_generic/States.hpp"

using CT = coffee::CoffeeType;
using CS = coffee::CupSize;

TEST(ClassicGenericCoffeeMachine, StartsInReady) {
    cg::CoffeeMachine m;
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.data().order.has_value());
}

TEST(ClassicGenericCoffeeMachine, HappyPath) {
    cg::CoffeeMachine m;
    m.selectCoffee({CT::Cappuccino, CS::Large});
    EXPECT_EQ(m.stateName(), "Grinding");
    EXPECT_EQ(m.data().order->type, CT::Cappuccino);

    m.grindDone();
    EXPECT_EQ(m.stateName(), "Brewing");

    m.brewDone();
    EXPECT_EQ(m.stateName(), "Dispensing");

    m.dispenseDone();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.data().order.has_value());
}

TEST(ClassicGenericCoffeeMachine, CancelDuringGrinding) {
    cg::CoffeeMachine m;
    m.selectCoffee({CT::Latte, CS::Small});
    m.cancel();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.data().order.has_value());
}

TEST(ClassicGenericCoffeeMachine, FaultAndReset) {
    cg::CoffeeMachine m;
    m.selectCoffee({CT::Americano, CS::Medium});
    m.grindDone();
    m.fault("Pump failure");
    EXPECT_EQ(m.stateName(), "Error");
    EXPECT_EQ(m.data().faultReason, "Pump failure");

    m.reset();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_TRUE(m.data().faultReason.empty());
}

TEST(ClassicGenericCoffeeMachine, ProfileStoredInData) {
    cg::CoffeeMachine m;
    m.selectCoffee({CT::Espresso, CS::Large});
    EXPECT_TRUE(m.data().profile.has_value());
    EXPECT_EQ(m.data().profile->grindLevel, 8);
    EXPECT_FLOAT_EQ(m.data().profile->waterMl, 90.f);
}
