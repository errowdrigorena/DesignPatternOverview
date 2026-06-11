#pragma once

#include <iosfwd>
#include <string_view>

namespace facade_pattern_classic {

class Projector {
public:
    explicit Projector(std::ostream& out);

    void on() const;
    void wide_screen_mode() const;
    void display(std::string_view title) const;
    void off() const;

private:
    std::ostream& out_;
};

}  // namespace facade_pattern_classic
