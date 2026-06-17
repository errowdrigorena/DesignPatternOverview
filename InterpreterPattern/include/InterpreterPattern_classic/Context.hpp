#pragma once

#include <string>
#include <unordered_map>

namespace interpreter_pattern_classic {

class Context {
public:
    void set(std::string name, bool value);
    [[nodiscard]] bool get(const std::string& name) const;
    [[nodiscard]] bool contains(const std::string& name) const;

private:
    std::unordered_map<std::string, bool> values_;
};

}  // namespace interpreter_pattern_classic
