#pragma once

#include <iosfwd>
#include <string_view>

namespace facade_pattern_classic {

class Amplifier {
public:
    explicit Amplifier(std::ostream& out);

    void on() const;
    void set_volume(int volume) const;
    void connect(std::string_view source) const;
    void off() const;

private:
    std::ostream& out_;
};

}  // namespace facade_pattern_classic
