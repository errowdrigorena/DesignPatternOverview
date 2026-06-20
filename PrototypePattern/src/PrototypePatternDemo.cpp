#include <PrototypePattern_classic/CirclePrototype.hpp>
#include <PrototypePattern_classic/RectanglePrototype.hpp>
#include <PrototypePattern_classic/ShapePrototype.hpp>

#include <iostream>
#include <memory>

int main()
{
    using prototype_pattern_classic::CirclePrototype;
    using prototype_pattern_classic::RectanglePrototype;
    using prototype_pattern_classic::ShapePrototype;

    const CirclePrototype selection_handle{"selection-handle", "blue", 0.0, 0.0, 6.0};
    const RectanglePrototype selection_box{"selection-box", "blue", 0.0, 0.0, 120.0, 80.0};

    std::unique_ptr<ShapePrototype> moved_handle{selection_handle.clone()};
    moved_handle->set_name("selection-handle-copy");
    moved_handle->set_color("orange");
    moved_handle->move_to(40.0, 24.0);

    std::unique_ptr<ShapePrototype> moved_box{selection_box.clone()};
    moved_box->set_name("selection-box-copy");
    moved_box->move_to(30.0, 18.0);

    selection_handle.draw(std::cout);
    moved_handle->draw(std::cout);
    selection_box.draw(std::cout);
    moved_box->draw(std::cout);

    return 0;
}
