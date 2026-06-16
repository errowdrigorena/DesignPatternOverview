#pragma once

#include <optional>
#include <string>
#include <vector>

namespace memento_pattern_modern::persistent {

enum class ShapeKind {
    circle,
    rectangle
};

struct ShapeRecord {
    ShapeKind kind;
    std::string name;
    double first_dimension{};
    double second_dimension{};
};

class ShapeCanvas {
public:
    ShapeCanvas() = default;

    [[nodiscard]] ShapeCanvas added_circle(std::string name, double radius) const;
    [[nodiscard]] ShapeCanvas added_rectangle(std::string name, double width, double height) const;
    [[nodiscard]] ShapeCanvas selected(const std::string& name) const;

    [[nodiscard]] std::vector<std::string> shape_names() const;
    [[nodiscard]] std::optional<std::string> selected_shape() const;

private:
    explicit ShapeCanvas(std::vector<ShapeRecord> shapes, std::optional<std::string> selected_shape);

    [[nodiscard]] bool contains_shape(const std::string& name) const;

    std::vector<ShapeRecord> shapes_;
    std::optional<std::string> selected_shape_;
};

}  // namespace memento_pattern_modern::persistent
