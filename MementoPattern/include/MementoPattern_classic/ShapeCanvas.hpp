#pragma once

#include <optional>
#include <string>
#include <vector>

namespace memento_pattern_classic {

class CanvasSnapshot {
public:
    [[nodiscard]] std::size_t shape_count() const;

private:
    friend class ShapeCanvas;

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

    CanvasSnapshot(std::vector<ShapeRecord> shapes, std::optional<std::string> selected_shape);

    std::vector<ShapeRecord> shapes_;
    std::optional<std::string> selected_shape_;
};

class ShapeCanvas {
public:
    void add_circle(std::string name, double radius);
    void add_rectangle(std::string name, double width, double height);
    void select(const std::string& name);

    [[nodiscard]] std::vector<std::string> shape_names() const;
    [[nodiscard]] std::optional<std::string> selected_shape() const;

    [[nodiscard]] CanvasSnapshot save() const;
    void restore(const CanvasSnapshot& snapshot);

private:
    using ShapeRecord = CanvasSnapshot::ShapeRecord;
    using ShapeKind = CanvasSnapshot::ShapeKind;

    [[nodiscard]] bool contains_shape(const std::string& name) const;

    std::vector<ShapeRecord> shapes_;
    std::optional<std::string> selected_shape_;
};

}  // namespace memento_pattern_classic
