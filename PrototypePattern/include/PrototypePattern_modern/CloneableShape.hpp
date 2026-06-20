#pragma once

#include <PrototypePattern_modern/ShapePrototype.hpp>

#include <memory>

namespace prototype_pattern_modern {

template <typename Derived>
class CloneableShape : public ShapePrototype {
public:
    [[nodiscard]] std::unique_ptr<ShapePrototype> clone() const override
    {
        return std::make_unique<Derived>(static_cast<const Derived&>(*this));
    }
};

}  // namespace prototype_pattern_modern
