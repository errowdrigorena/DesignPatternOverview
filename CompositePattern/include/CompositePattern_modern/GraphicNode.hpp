#pragma once

#include <iosfwd>
#include <cstddef>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace composite_pattern_modern {

class Group;

struct Shape {
    std::string name;
    double area{};
};

using Node = std::variant<Shape, std::shared_ptr<Group>>;

class Group {
public:
    explicit Group(std::string name);
    Group(std::string name, std::vector<Node> children);

    void add(Node child);

    [[nodiscard]] const std::string& name() const;
    [[nodiscard]] const std::vector<Node>& children() const;
    [[nodiscard]] std::size_t child_count() const;

private:
    std::string name_;
    std::vector<Node> children_;
};

[[nodiscard]] Shape shape(std::string name, double area);
[[nodiscard]] Node group(std::string name, std::vector<Node> children = {});

[[nodiscard]] double area(const Node& node);
void render(const Node& node, std::ostream& output, int depth = 0);

}  // namespace composite_pattern_modern
