#include <FacadePattern_classic/HomeTheaterFacade.hpp>

namespace facade_pattern_classic {

HomeTheaterFacade::HomeTheaterFacade(
    Amplifier& amplifier,
    Projector& projector,
    StreamingPlayer& player)
    : amplifier_{amplifier}
    , projector_{projector}
    , player_{player}
{
}

void HomeTheaterFacade::watch_movie(const std::string_view title, const bool subtitles) const
{
    player_.on();
    player_.select_movie(title);

    amplifier_.on();
    amplifier_.connect("streaming player");
    amplifier_.set_volume(65);

    projector_.on();
    projector_.wide_screen_mode();
    projector_.display(title);

    if (subtitles) {
        player_.enable_subtitles();
    }

    player_.play();
}

void HomeTheaterFacade::end_movie() const
{
    player_.stop();
    projector_.off();
    amplifier_.off();
    player_.off();
}

}  // namespace facade_pattern_classic
