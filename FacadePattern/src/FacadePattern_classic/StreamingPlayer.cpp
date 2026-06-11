#include <FacadePattern_classic/StreamingPlayer.hpp>

#include <iostream>

namespace facade_pattern_classic {

StreamingPlayer::StreamingPlayer(std::ostream& out)
    : out_{out}
{
}

void StreamingPlayer::on() const
{
    out_ << "Streaming player on\n";
}

void StreamingPlayer::select_movie(const std::string_view title) const
{
    out_ << "Streaming player selected " << title << '\n';
}

void StreamingPlayer::enable_subtitles() const
{
    out_ << "Streaming player subtitles enabled\n";
}

void StreamingPlayer::play() const
{
    out_ << "Streaming player playing\n";
}

void StreamingPlayer::stop() const
{
    out_ << "Streaming player stopped\n";
}

void StreamingPlayer::off() const
{
    out_ << "Streaming player off\n";
}

}  // namespace facade_pattern_classic
