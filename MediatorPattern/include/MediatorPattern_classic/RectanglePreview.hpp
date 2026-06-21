#pragma once

#include <MediatorPattern_classic/Component.hpp>

#include <cstddef>
#include <iosfwd>

namespace mediator_pattern_classic {

class RectanglePreview final : public Component {
public:
    RectanglePreview(Mediator& mediator, std::ostream& output);

    void show(double width, double height);

    [[nodiscard]] double displayed_width() const;
    [[nodiscard]] double displayed_height() const;
    [[nodiscard]] std::size_t update_count() const;

private:
    std::ostream& output_;
    double displayed_width_{};
    double displayed_height_{};
    std::size_t update_count_{};
};

}  // namespace mediator_pattern_classic
