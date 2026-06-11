#include <FacadePattern_classic/Amplifier.hpp>

#include <iostream>

namespace facade_pattern_classic {

Amplifier::Amplifier(std::ostream& out)
    : out_{out}
{
}

void Amplifier::on() const
{
    out_ << "Amplifier on\n";
}

void Amplifier::set_volume(const int volume) const
{
    out_ << "Amplifier volume set to " << volume << '\n';
}

void Amplifier::connect(const std::string_view source) const
{
    out_ << "Amplifier connected to " << source << '\n';
}

void Amplifier::off() const
{
    out_ << "Amplifier off\n";
}

}  // namespace facade_pattern_classic
