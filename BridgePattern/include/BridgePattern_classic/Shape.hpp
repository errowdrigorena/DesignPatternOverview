#pragma once

#include <BridgePattern_classic/ShapeRenderer.hpp>

#include <memory>
#include <string_view>

namespace bridge_pattern_classic {

class Shape {
public:
    explicit Shape(std::shared_ptr<const ShapeRenderer> renderer);
    virtual ~Shape() = default;

    void set_renderer(std::shared_ptr<const ShapeRenderer> renderer);
    void draw() const;

protected:
    [[nodiscard]] virtual std::string_view name() const = 0;
    [[nodiscard]] virtual bridge_pattern_common::ShapePath outline() const = 0;

private:
    std::shared_ptr<const ShapeRenderer> renderer_;
};

}  // namespace bridge_pattern_classic
