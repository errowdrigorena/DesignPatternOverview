#include <CompositePattern_modern/GraphicNode.hpp>

#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace composite_pattern_modern {

namespace {

void validate_name(const std::string& name, const char* type)
{
    if (name.empty()) {
        throw std::invalid_argument(std::string{type} + " requires a name");
    }
}

}  // namespace

Group::Group(std::string name)
    : name_{std::move(name)}
{
    validate_name(name_, "A group");
}

Group::Group(std::string name, std::vector<Node> children)
    : name_{std::move(name)}
    , children_{std::move(children)}
{
    validate_name(name_, "A group");
}

void Group::add(Node child)
{
    children_.push_back(std::move(child));
}

const std::string& Group::name() const
{
    return name_;
}

const std::vector<Node>& Group::children() const
{
    return children_;
}

std::size_t Group::child_count() const
{
    return children_.size();
}

Shape shape(std::string name, const double area)
{
    validate_name(name, "A shape");

    if (area < 0.0) {
        throw std::invalid_argument("A shape area cannot be negative");
    }

    return Shape{std::move(name), area};
}

Node group(std::string name, std::vector<Node> children)
{
    return std::make_shared<Group>(std::move(name), std::move(children));
}

double area(const Node& node)
{
    return std::visit(
        [](const auto& value) -> double {
            using Value = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<Value, Shape>) {
                return value.area;
            } else {
                if (!value) {
                    throw std::invalid_argument("A group node cannot be null");
                }

                double total{};
                for (const auto& child : value->children()) {
                    total += area(child);
                }

                return total;
            }
        },
        node);
}

void render(const Node& node, std::ostream& output, const int depth)
{
    std::visit(
        [&](const auto& value) {
            using Value = std::decay_t<decltype(value)>;
            const auto indent = std::string(static_cast<std::size_t>(depth) * 2U, ' ');

            if constexpr (std::is_same_v<Value, Shape>) {
                output << indent << "- " << value.name << " (" << value.area << ")\n";
            } else {
                if (!value) {
                    throw std::invalid_argument("A group node cannot be null");
                }

                output << indent << "+ " << value->name() << " (" << area(node) << ")\n";

                for (const auto& child : value->children()) {
                    render(child, output, depth + 1);
                }
            }
        },
        node);
}

}  // namespace composite_pattern_modern
