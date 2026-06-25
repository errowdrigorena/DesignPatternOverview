#pragma once

#include <CompositePattern_classic/Graphic.hpp>

#include <string>

namespace composite_pattern_classic {

class ShapeLeaf final : public Graphic {
public:
    ShapeLeaf(std::string name, double area);

    [[nodiscard]] double area() const override;
    void render(std::ostream& output, int depth = 0) const override;

private:
    std::string name_;
    double area_{};
};

}  // namespace composite_pattern_classic
