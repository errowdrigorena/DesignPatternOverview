#pragma once

#include <BridgePattern_classic/Shape.hpp>

namespace bridge_pattern_classic {

class RectangleShape final : public Shape {
public:
    RectangleShape(double width, double height, std::shared_ptr<const ShapeRenderer> renderer);

private:
    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] bridge_pattern_common::ShapePath outline() const override;

    double width_;
    double height_;
};

}  // namespace bridge_pattern_classic
