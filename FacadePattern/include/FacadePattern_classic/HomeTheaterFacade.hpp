#pragma once

#include <FacadePattern_classic/Amplifier.hpp>
#include <FacadePattern_classic/Projector.hpp>
#include <FacadePattern_classic/StreamingPlayer.hpp>

#include <string_view>

namespace facade_pattern_classic {

class HomeTheaterFacade {
public:
    HomeTheaterFacade(Amplifier& amplifier, Projector& projector, StreamingPlayer& player);

    void watch_movie(std::string_view title, bool subtitles) const;
    void end_movie() const;

private:
    Amplifier& amplifier_;
    Projector& projector_;
    StreamingPlayer& player_;
};

}  // namespace facade_pattern_classic
