#pragma once

#include <string_view>

namespace builder_pattern_classic {

class RectangleBuilder {
public:
    virtual ~RectangleBuilder() = default;

    virtual void reset() = 0;
    virtual void set_name(std::string_view name) = 0;
    virtual void set_width(double width) = 0;
    virtual void set_height(double height) = 0;
};

}  // namespace builder_pattern_classic
