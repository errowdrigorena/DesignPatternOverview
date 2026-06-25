#pragma once

#include <CompositePattern_classic/Graphic.hpp>

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace composite_pattern_classic {

class ShapeGroup final : public Graphic {
public:
    explicit ShapeGroup(std::string name);

    void add(std::unique_ptr<Graphic> graphic);
    [[nodiscard]] std::size_t child_count() const;

    [[nodiscard]] double area() const override;
    void render(std::ostream& output, int depth = 0) const override;

private:
    std::string name_;
    std::vector<std::unique_ptr<Graphic>> children_;
};

}  // namespace composite_pattern_classic
