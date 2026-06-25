#pragma once
#include <memory>
#include <string_view>

// Generic reusable engine: decouples state storage/transition from any
// specific domain. Derive from it passing the concrete machine as Derived
// so each domain gets its own strongly-typed interface without boilerplate.
template<typename StateIface, typename ContextData>
class StateEngine {
public:
    explicit StateEngine(std::unique_ptr<StateIface> initial, ContextData ctx = {})
        : _state(std::move(initial)), _data(std::move(ctx)) {}

    void transitionTo(std::unique_ptr<StateIface> next) {
        _state = std::move(next);
    }

    std::string_view stateName() const { return _state->name(); }

    ContextData&       data()       { return _data; }
    const ContextData& data() const { return _data; }

protected:
    std::unique_ptr<StateIface> _state;
    ContextData                 _data;
};
