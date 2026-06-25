#include <gtest/gtest.h>
#include "StatePattern_variant/CoffeeMachine.hpp"

using CT = coffee::CoffeeType;
using CS = coffee::CupSize;

TEST(VariantCoffeeMachine, StartsInReady) {
    sv::CoffeeMachine m;
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_TRUE(std::holds_alternative<sv::ReadyState>(m.state()));
}

TEST(VariantCoffeeMachine, HappyPath) {
    sv::CoffeeMachine m;
    m.process(sv::EvSelectCoffee{{CT::Americano, CS::Medium}});
    EXPECT_EQ(m.stateName(), "Grinding");
    EXPECT_EQ(m.currentOrder()->type, CT::Americano);

    m.process(sv::EvGrindDone{});
    EXPECT_EQ(m.stateName(), "Brewing");

    m.process(sv::EvBrewDone{});
    EXPECT_EQ(m.stateName(), "Dispensing");

    m.process(sv::EvDispenseDone{});
    EXPECT_EQ(m.stateName(), "Ready");
    EXPECT_FALSE(m.hasOrder());
}

TEST(VariantCoffeeMachine, CancelDuringGrinding) {
    sv::CoffeeMachine m;
    m.process(sv::EvSelectCoffee{{CT::Espresso, CS::Small}});
    m.process(sv::EvCancel{});
    EXPECT_EQ(m.stateName(), "Ready");
}

TEST(VariantCoffeeMachine, FaultFromGrinding) {
    sv::CoffeeMachine m;
    m.process(sv::EvSelectCoffee{{CT::Latte, CS::Large}});
    m.process(sv::EvFault{"Grinder jam"});
    EXPECT_EQ(m.stateName(), "Error");
    EXPECT_EQ(std::get<sv::ErrorState>(m.state()).reason, "Grinder jam");
}

TEST(VariantCoffeeMachine, ResetFromError) {
    sv::CoffeeMachine m;
    m.process(sv::EvSelectCoffee{{CT::Cappuccino, CS::Medium}});
    m.process(sv::EvFault{"Boiler fault"});
    m.process(sv::EvReset{});
    EXPECT_EQ(m.stateName(), "Ready");
}

TEST(VariantCoffeeMachine, IgnoredEventsPreserveState) {
    sv::CoffeeMachine m;
    m.process(sv::EvGrindDone{});     // ignored when Ready
    m.process(sv::EvBrewDone{});      // ignored when Ready
    EXPECT_EQ(m.stateName(), "Ready");
}

TEST(VariantCoffeeMachine, StateCarriesProfile) {
    sv::CoffeeMachine m;
    m.process(sv::EvSelectCoffee{{CT::Espresso, CS::Small}});
    const auto& gs = std::get<sv::GrindingState>(m.state());
    EXPECT_EQ(gs.profile.grindLevel, 8);
    EXPECT_FLOAT_EQ(gs.profile.waterMl, 30.f);
}
