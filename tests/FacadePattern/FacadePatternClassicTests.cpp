#include <FacadePattern_classic/Amplifier.hpp>
#include <FacadePattern_classic/HomeTheaterFacade.hpp>
#include <FacadePattern_classic/Projector.hpp>
#include <FacadePattern_classic/StreamingPlayer.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace {

using facade_pattern_classic::Amplifier;
using facade_pattern_classic::HomeTheaterFacade;
using facade_pattern_classic::Projector;
using facade_pattern_classic::StreamingPlayer;

TEST(ClassicFacadeAmplifier, WritesEveryOperation)
{
    std::ostringstream output;
    const Amplifier amplifier{output};

    amplifier.on();
    amplifier.connect("streaming player");
    amplifier.set_volume(65);
    amplifier.off();

    EXPECT_EQ(
        output.str(),
        "Amplifier on\n"
        "Amplifier connected to streaming player\n"
        "Amplifier volume set to 65\n"
        "Amplifier off\n");
}

TEST(ClassicFacadeProjector, WritesEveryOperation)
{
    std::ostringstream output;
    const Projector projector{output};

    projector.on();
    projector.wide_screen_mode();
    projector.display("Blade Runner");
    projector.off();

    EXPECT_EQ(
        output.str(),
        "Projector on\n"
        "Projector in wide screen mode\n"
        "Projector displaying Blade Runner\n"
        "Projector off\n");
}

TEST(ClassicFacadeStreamingPlayer, WritesEveryOperation)
{
    std::ostringstream output;
    const StreamingPlayer player{output};

    player.on();
    player.select_movie("Blade Runner");
    player.enable_subtitles();
    player.play();
    player.stop();
    player.off();

    EXPECT_EQ(
        output.str(),
        "Streaming player on\n"
        "Streaming player selected Blade Runner\n"
        "Streaming player subtitles enabled\n"
        "Streaming player playing\n"
        "Streaming player stopped\n"
        "Streaming player off\n");
}

TEST(ClassicHomeTheaterFacade, WatchMovieCoordinatesSubsystemsWithSubtitles)
{
    std::ostringstream output;
    Amplifier amplifier{output};
    Projector projector{output};
    StreamingPlayer player{output};
    const HomeTheaterFacade home_theater{amplifier, projector, player};

    home_theater.watch_movie("Blade Runner", true);

    EXPECT_EQ(
        output.str(),
        "Streaming player on\n"
        "Streaming player selected Blade Runner\n"
        "Amplifier on\n"
        "Amplifier connected to streaming player\n"
        "Amplifier volume set to 65\n"
        "Projector on\n"
        "Projector in wide screen mode\n"
        "Projector displaying Blade Runner\n"
        "Streaming player subtitles enabled\n"
        "Streaming player playing\n");
}

TEST(ClassicHomeTheaterFacade, WatchMovieSkipsSubtitlesWhenDisabled)
{
    std::ostringstream output;
    Amplifier amplifier{output};
    Projector projector{output};
    StreamingPlayer player{output};
    const HomeTheaterFacade home_theater{amplifier, projector, player};

    home_theater.watch_movie("Alien", false);

    EXPECT_EQ(
        output.str(),
        "Streaming player on\n"
        "Streaming player selected Alien\n"
        "Amplifier on\n"
        "Amplifier connected to streaming player\n"
        "Amplifier volume set to 65\n"
        "Projector on\n"
        "Projector in wide screen mode\n"
        "Projector displaying Alien\n"
        "Streaming player playing\n");
}

TEST(ClassicHomeTheaterFacade, EndMovieShutsDownSubsystemsInOrder)
{
    std::ostringstream output;
    Amplifier amplifier{output};
    Projector projector{output};
    StreamingPlayer player{output};
    const HomeTheaterFacade home_theater{amplifier, projector, player};

    home_theater.end_movie();

    EXPECT_EQ(
        output.str(),
        "Streaming player stopped\n"
        "Projector off\n"
        "Amplifier off\n"
        "Streaming player off\n");
}

}  // namespace
