#pragma once

#include <iosfwd>
#include <string_view>

namespace facade_pattern_classic {

class StreamingPlayer {
public:
    explicit StreamingPlayer(std::ostream& out);

    void on() const;
    void select_movie(std::string_view title) const;
    void enable_subtitles() const;
    void play() const;
    void stop() const;
    void off() const;

private:
    std::ostream& out_;
};

}  // namespace facade_pattern_classic
