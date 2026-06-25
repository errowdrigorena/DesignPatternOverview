#include "StatePattern_table/CoffeeMachine.hpp"
#include <iostream>

int main() {
    std::cout << "=== Table-based State Pattern (FSM + Orchestrator) — Coffee Machine ===\n\n";

    // ── 1. Normal immediate dispatch ─────────────────────────────────────────
    {
        tbl::CoffeeMachine m;
        std::cout << "--- 1. Happy path (immediate dispatch) ---\n";
        m.selectCoffee({coffee::CoffeeType::Espresso, coffee::CupSize::Medium});
        m.grindDone();
        m.brewDone();
        m.dispenseDone();
        std::cout << "State: " << m.stateName() << "\n\n";
    }

    // ── 2. Batch mode — priority wins ────────────────────────────────────────
    // Push a normal cycle AND a fault into the queue before processing.
    // The fault (priority 0) must be processed before SelectCoffee (priority 10).
    {
        tbl::CoffeeMachine m;
        std::cout << "--- 2. Batch + priority: fault preempts SelectCoffee ---\n";

        // Load both events without processing:
        m.pushSelectCoffee({coffee::CoffeeType::Latte, coffee::CupSize::Large},
                           tbl::CoffeeMachine::kNormalPriority);   // priority 10
        m.pushFault("Boiler overheat",
                    tbl::CoffeeMachine::kFaultPriority);            // priority 0

        // Now drain the queue — Fault fires first
        m.processAll();

        // Ready received a Fault → Error.  SelectCoffee fired next in Error → ignored.
        std::cout << "State: " << m.stateName()
                  << "  |  fault reason: " << m.context().faultReason << "\n\n";
    }

    // ── 3. Cancel has higher priority than pending GrindDone ─────────────────
    {
        tbl::CoffeeMachine m;
        std::cout << "--- 3. Batch + priority: cancel preempts GrindDone ---\n";

        m.selectCoffee({coffee::CoffeeType::Cappuccino, coffee::CupSize::Small}); // immediate

        // Now load GrindDone (normal=10) and Cancel (cancel=5) together
        m.pushGrindDone(tbl::CoffeeMachine::kNormalPriority);
        m.pushCancel   (tbl::CoffeeMachine::kCancelPriority);
        m.processAll();  // Cancel(5) fires before GrindDone(10) → back to Ready

        std::cout << "State: " << m.stateName() << "  (expected: Ready)\n\n";
    }

    // ── 4. Reset after fault ──────────────────────────────────────────────────
    {
        tbl::CoffeeMachine m;
        std::cout << "--- 4. Fault then reset ---\n";
        m.selectCoffee({coffee::CoffeeType::Americano, coffee::CupSize::Large});
        m.grindDone();
        m.fault("Water tank empty");
        m.reset();
        std::cout << "Final state: " << m.stateName() << "\n";
    }
}
