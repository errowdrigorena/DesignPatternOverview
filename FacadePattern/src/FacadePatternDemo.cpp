#include <FacadePattern_classic/Amplifier.hpp>
#include <FacadePattern_classic/HomeTheaterFacade.hpp>
#include <FacadePattern_classic/Projector.hpp>
#include <FacadePattern_classic/StreamingPlayer.hpp>

#include <iostream>

int main()
{
    using namespace facade_pattern_classic;

    Amplifier amplifier{std::cout};
    Projector projector{std::cout};
    StreamingPlayer player{std::cout};

    const HomeTheaterFacade home_theater{amplifier, projector, player};

    home_theater.watch_movie("2001: A Space Odyssey", true);
    home_theater.end_movie();

    return 0;
}
