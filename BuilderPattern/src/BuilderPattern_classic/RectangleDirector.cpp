#include <BuilderPattern_classic/RectangleDirector.hpp>

namespace builder_pattern_classic {

void RectangleDirector::construct(
    RectangleBuilder& builder,
    const std::string_view name,
    const double width,
    const double height) const
{
    builder.reset();
    builder.set_name(name);
    builder.set_width(width);
    builder.set_height(height);
}

}  // namespace builder_pattern_classic
