#include <gtest/gtest.h>
#include "StatePattern_classic/CoffeeMachine.hpp"

using CT = coffee::CoffeeType;
using CS = coffee::CupSize;

TEST(ClassicCoffeeMachine, StartsInReady) {
    CoffeeMachine m;
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.hasOrder());
}

TEST(ClassicCoffeeMachine, HappyPath) {
    CoffeeMachine m;
    m.selectCoffee({CT::Espresso, CS::Small});
    EXPECT_EQ(m.stateName(), "Grinding");
    EXPECT_TRUE(m.hasOrder());
    EXPECT_EQ(m.currentOrder().type, CT::Espresso);

    m.grindDone();
    EXPECT_EQ(m.stateName(), "Brewing");

    m.brewDone();
    EXPECT_EQ(m.stateName(), "Dispensing");

    m.dispenseDone();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.hasOrder());
}

TEST(ClassicCoffeeMachine, CancelDuringGrinding) {
    CoffeeMachine m;
    m.selectCoffee({CT::Latte, CS::Large});
    EXPECT_EQ(m.stateName(), "Grinding");

    m.cancel();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.hasOrder());
}

TEST(ClassicCoffeeMachine, FaultFromAnyActiveState) {
    for (auto steps : {0, 1, 2, 3}) {
        CoffeeMachine m;
        m.selectCoffee({CT::Americano, CS::Medium});
        if (steps >= 1) m.grindDone();
        if (steps >= 2) m.brewDone();
        if (steps >= 3) m.dispenseDone();  // back to Ready at step 4

        if (steps < 3) {
            m.fault("Hardware error");
            EXPECT_EQ(m.stateName(), "Error");
            EXPECT_EQ(m.faultReason(), "Hardware error");
        }
    }
}

TEST(ClassicCoffeeMachine, ResetFromError) {
    CoffeeMachine m;
    m.selectCoffee({CT::Cappuccino, CS::Medium});
    m.fault("Sensor failure");
    EXPECT_EQ(m.stateName(), "Error");

    m.reset();
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.hasOrder());
    EXPECT_TRUE(m.faultReason().empty());
}

TEST(ClassicCoffeeMachine, IgnoredEventsDoNotChangeState) {
    CoffeeMachine m;
    // GrindDone/BrewDone/DispenseDone when Ready — all no-ops
    m.grindDone();
    m.brewDone();
    m.dispenseDone();
    EXPECT_EQ(m.stateName(), "Ready");
}

TEST(ClassicCoffeeMachine, ProfileIsComputedOnSelection) {
    CoffeeMachine m;
    m.selectCoffee({CT::Espresso, CS::Medium});
    EXPECT_EQ(m.currentProfile().grindLevel, 8);
    EXPECT_FLOAT_EQ(m.currentProfile().waterMl, 60.f);
    EXPECT_FLOAT_EQ(m.currentProfile().temperatureC, 94.f);
}
