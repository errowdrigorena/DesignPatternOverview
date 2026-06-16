#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace memento_pattern_modern::nested_snapshot {

class ShapeCanvas {
public:
    class Snapshot {
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

        Snapshot(std::vector<ShapeRecord> shapes, std::optional<std::string> selected_shape);

        std::vector<ShapeRecord> shapes_;
        std::optional<std::string> selected_shape_;
    };

    void add_circle(std::string name, double radius);
    void add_rectangle(std::string name, double width, double height);
    void select(const std::string& name);

    [[nodiscard]] std::vector<std::string> shape_names() const;
    [[nodiscard]] std::optional<std::string> selected_shape() const;

    [[nodiscard]] Snapshot snapshot() const;
    void restore(const Snapshot& snapshot);

private:
    using ShapeRecord = Snapshot::ShapeRecord;
    using ShapeKind = Snapshot::ShapeKind;

    [[nodiscard]] bool contains_shape(const std::string& name) const;

    std::vector<ShapeRecord> shapes_;
    std::optional<std::string> selected_shape_;
};

}  // namespace memento_pattern_modern::nested_snapshot
