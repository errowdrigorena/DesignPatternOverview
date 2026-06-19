#pragma once

#include <Shapes_traditional/Shapes.hpp>

#include <memory>
#include <ostream>

namespace factory_method_pattern_classic {

class ShapeCreator {
public:
    virtual ~ShapeCreator() = default;

    [[nodiscard]] std::unique_ptr<shapes_traditional::Shapes> create() const
    {
        return create_shape();
    }

    void render_preview(std::ostream& out) const
    {
        const auto shape = create_shape();
        shape->draw();
        out << "Area: " << shape->calculate_area() << '\n';
    }

    [[nodiscard]] double preview_area() const
    {
        return create_shape()->calculate_area();
    }

private:
    [[nodiscard]] virtual std::unique_ptr<shapes_traditional::Shapes> create_shape() const = 0;
};

}  // namespace factory_method_pattern_classic
