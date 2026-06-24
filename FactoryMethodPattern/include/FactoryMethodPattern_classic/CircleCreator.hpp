#pragma once

#include <FactoryMethodPattern_classic/ShapeCreator.hpp>

namespace factory_method_pattern_classic {

class CircleCreator final : public ShapeCreator {
private:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shape> create_shape() const override;
};

}  // namespace factory_method_pattern_classic
