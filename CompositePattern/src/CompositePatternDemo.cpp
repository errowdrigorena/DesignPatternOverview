#include <CompositePattern_classic/ShapeGroup.hpp>
#include <CompositePattern_classic/ShapeLeaf.hpp>

#include <iostream>
#include <memory>

int main()
{
    auto toolbar = std::make_unique<composite_pattern_classic::ShapeGroup>("Toolbar icons");
    toolbar->add(std::make_unique<composite_pattern_classic::ShapeLeaf>("Save icon", 12.0));
    toolbar->add(std::make_unique<composite_pattern_classic::ShapeLeaf>("Open icon", 10.0));

    composite_pattern_classic::ShapeGroup screen{"Main screen"};
    screen.add(std::make_unique<composite_pattern_classic::ShapeLeaf>("Canvas", 80.0));
    screen.add(std::move(toolbar));

    screen.render(std::cout);
}
