#include <MediatorPattern_classic/RectanglePreview.hpp>

#include <ostream>

namespace mediator_pattern_classic {

RectanglePreview::RectanglePreview(Mediator& mediator, std::ostream& output)
    : Component{mediator}
    , output_{output}
{
}

void RectanglePreview::show(double width, double height)
{
    displayed_width_ = width;
    displayed_height_ = height;
    ++update_count_;

    output_ << "Preview: " << width << " x " << height << '\n';
}

double RectanglePreview::displayed_width() const
{
    return displayed_width_;
}

double RectanglePreview::displayed_height() const
{
    return displayed_height_;
}

std::size_t RectanglePreview::update_count() const
{
    return update_count_;
}

}  // namespace mediator_pattern_classic
