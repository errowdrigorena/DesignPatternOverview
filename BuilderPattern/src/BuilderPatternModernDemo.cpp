#include <BuilderPattern_modern/RectangleBuilder.hpp>

#include <iostream>

int main()
{
    const auto rectangle = builder_pattern_modern::RectangleBuilder{}
                           .name("selection-box")
                           .width(120.0)
                           .height(80.0)
                           .build();

    std::cout << rectangle.name() << ": " << rectangle.width() << " x " << rectangle.height() << '\n';
}
