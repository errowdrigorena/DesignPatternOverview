#include <PrototypePattern_modern/CirclePrototype.hpp>
#include <PrototypePattern_modern/RectanglePrototype.hpp>
#include <PrototypePattern_modern/ShapePrototype.hpp>

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

int main()
{
    using prototype_pattern_modern::CirclePrototype;
    using prototype_pattern_modern::RectanglePrototype;
    using prototype_pattern_modern::ShapePrototype;

    std::vector<std::unique_ptr<ShapePrototype>> palette;
    palette.push_back(std::make_unique<CirclePrototype>("port", "green", 0.0, 0.0, 8.0));
    palette.push_back(std::make_unique<RectanglePrototype>("node", "green", 0.0, 0.0, 96.0, 48.0));

    std::vector<std::unique_ptr<ShapePrototype>> diagram_shapes;

    for (const auto& prototype : palette) {
        auto shape = prototype->clone();
        shape->set_color("purple");
        shape->move_to(32.0, 24.0);
        diagram_shapes.push_back(std::move(shape));
    }

    for (const auto& prototype : palette) {
        prototype->draw(std::cout);
    }

    for (const auto& shape : diagram_shapes) {
        shape->draw(std::cout);
    }

    return 0;
}
