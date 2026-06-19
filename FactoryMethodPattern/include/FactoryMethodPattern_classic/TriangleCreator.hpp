#pragma once

#include <FactoryMethodPattern_classic/ShapeCreator.hpp>

namespace factory_method_pattern_classic {

class TriangleCreator final : public ShapeCreator {
private:
    [[nodiscard]] std::unique_ptr<shapes_traditional::Shapes> create_shape() const override;
};

}  // namespace factory_method_pattern_classic
