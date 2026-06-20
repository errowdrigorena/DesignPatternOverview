#include <BuilderPattern_classic/ConcreteRectangleBuilder.hpp>
#include <BuilderPattern_classic/RectangleDirector.hpp>

#include <iostream>

int main()
{
    builder_pattern_classic::ConcreteRectangleBuilder builder;
    const builder_pattern_classic::RectangleDirector director;
    director.construct(builder, "selection-box", 120.0, 80.0);

    const auto rectangle = builder.build();

    std::cout << rectangle.name() << ": " << rectangle.width() << " x " << rectangle.height() << '\n';
}
