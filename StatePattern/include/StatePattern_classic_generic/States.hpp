#pragma once
#include "ICoffeeMachineState.hpp"
#include <iostream>
#include <memory>

namespace cg {

template<typename T> class ReadyState;
template<typename T> class GrindingState;
template<typename T> class BrewingState;
template<typename T> class DispensingState;
template<typename T> class ErrorState;

// ── ReadyState ────────────────────────────────────────────────────────────────

template<typename T>
class ReadyState : public ICoffeeMachineState<T> {
public:
    void onSelectCoffee(T& machine, coffee::CoffeeOrder order) override {
        std::cout << "[Ready] → Grinding  ("
                  << coffee::name(order.type) << ", " << coffee::name(order.size) << ")\n";
        machine.data().order   = order;
        machine.data().profile = coffee::profileFor(order);
        machine.transitionTo(std::make_unique<GrindingState<T>>());
    }
    void onFault(T& machine, std::string_view reason) override {
        std::cout << "[Ready] FAULT: " << reason << "\n";
        machine.data().faultReason = std::string(reason);
        machine.transitionTo(std::make_unique<ErrorState<T>>());
    }
    std::string_view name() const override { return "Ready"; }
};

// ── GrindingState ─────────────────────────────────────────────────────────────

template<typename T>
class GrindingState : public ICoffeeMachineState<T> {
public:
    void onGrindDone(T& machine) override {
        std::cout << "[Grinding] → Brewing\n";
        machine.transitionTo(std::make_unique<BrewingState<T>>());
    }
    void onCancel(T& machine) override {
        std::cout << "[Grinding] cancelled → Ready\n";
        machine.data().order.reset();
        machine.data().profile.reset();
        machine.transitionTo(std::make_unique<ReadyState<T>>());
    }
    void onFault(T& machine, std::string_view reason) override {
        std::cout << "[Grinding] FAULT: " << reason << "\n";
        machine.data().faultReason = std::string(reason);
        machine.transitionTo(std::make_unique<ErrorState<T>>());
    }
    std::string_view name() const override { return "Grinding"; }
};

// ── BrewingState ──────────────────────────────────────────────────────────────

template<typename T>
class BrewingState : public ICoffeeMachineState<T> {
public:
    void onBrewDone(T& machine) override {
        std::cout << "[Brewing] → Dispensing\n";
        machine.transitionTo(std::make_unique<DispensingState<T>>());
    }
    void onFault(T& machine, std::string_view reason) override {
        std::cout << "[Brewing] FAULT: " << reason << "\n";
        machine.data().faultReason = std::string(reason);
        machine.transitionTo(std::make_unique<ErrorState<T>>());
    }
    std::string_view name() const override { return "Brewing"; }
};

// ── DispensingState ───────────────────────────────────────────────────────────

template<typename T>
class DispensingState : public ICoffeeMachineState<T> {
public:
    void onDispenseDone(T& machine) override {
        std::cout << "[Dispensing] done → Ready\n";
        machine.data().order.reset();
        machine.data().profile.reset();
        machine.transitionTo(std::make_unique<ReadyState<T>>());
    }
    void onFault(T& machine, std::string_view reason) override {
        std::cout << "[Dispensing] FAULT: " << reason << "\n";
        machine.data().faultReason = std::string(reason);
        machine.transitionTo(std::make_unique<ErrorState<T>>());
    }
    std::string_view name() const override { return "Dispensing"; }
};

// ── ErrorState ────────────────────────────────────────────────────────────────

template<typename T>
class ErrorState : public ICoffeeMachineState<T> {
public:
    void onReset(T& machine) override {
        std::cout << "[Error] reset → Ready\n";
        machine.data().order.reset();
        machine.data().profile.reset();
        machine.data().faultReason.clear();
        machine.transitionTo(std::make_unique<ReadyState<T>>());
    }
    void onFault(T& machine, std::string_view reason) override {
        std::cout << "[Error] additional fault: " << reason << "\n";
        machine.data().faultReason = std::string(reason);
    }
    std::string_view name() const override { return "Error"; }
};

} // namespace cg
