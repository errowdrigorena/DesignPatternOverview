#pragma once

#include <Shapes_strategy_classic/DrawStrategy.hpp>
#include <TestDoubles/Spies/DrawCall.hpp>

#include <memory>
#include <vector>

namespace test_doubles::spies {

class RecordingDrawStrategy final : public shapes_strategy::DrawStrategy {
public:
    explicit RecordingDrawStrategy(std::vector<DrawCall>& calls)
        : calls_{calls}
    {
    }

    void draw_circle(const double radius) const override
    {
        calls_.push_back({"circle", radius, std::nullopt});
    }

    void draw_rectangle(const double width, const double height) const override
    {
        calls_.push_back({"rectangle", width, height});
    }

    void draw_triangle(const double base, const double height) const override
    {
        calls_.push_back({"triangle", base, height});
    }

private:
    std::vector<DrawCall>& calls_;
};

inline std::unique_ptr<RecordingDrawStrategy> make_recording_strategy(std::vector<DrawCall>& calls)
{
    return std::make_unique<RecordingDrawStrategy>(calls);
}

}  // namespace test_doubles::spies
