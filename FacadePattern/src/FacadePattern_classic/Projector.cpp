#include <FacadePattern_classic/Projector.hpp>

#include <iostream>

namespace facade_pattern_classic {

Projector::Projector(std::ostream& out)
    : out_{out}
{
}

void Projector::on() const
{
    out_ << "Projector on\n";
}

void Projector::wide_screen_mode() const
{
    out_ << "Projector in wide screen mode\n";
}

void Projector::display(const std::string_view title) const
{
    out_ << "Projector displaying " << title << '\n';
}

void Projector::off() const
{
    out_ << "Projector off\n";
}

}  // namespace facade_pattern_classic
