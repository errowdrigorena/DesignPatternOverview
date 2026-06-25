#pragma once
#include <string_view>

namespace coffee {

enum class CoffeeType { Espresso, Cappuccino, Americano, Latte };
enum class CupSize    { Small, Medium, Large };

struct CoffeeOrder {
    CoffeeType type;
    CupSize    size;
    bool operator==(const CoffeeOrder&) const = default;
};

struct CoffeeProfile {
    float waterMl;
    int   grindLevel;   // 1=coarse … 10=fine
    float temperatureC;
};

inline CoffeeProfile profileFor(CoffeeOrder o) {
    float base = [](CupSize s) -> float {
        switch (s) {
            case CupSize::Small:  return 30.f;
            case CupSize::Medium: return 60.f;
            case CupSize::Large:  return 90.f;
        }
        return 60.f;
    }(o.size);

    switch (o.type) {
        case CoffeeType::Espresso:   return { base,        8, 94.f };
        case CoffeeType::Cappuccino: return { base * 2.f,  7, 92.f };
        case CoffeeType::Americano:  return { base * 4.f,  5, 90.f };
        case CoffeeType::Latte:      return { base * 3.f,  6, 92.f };
    }
    return { base, 5, 92.f };
}

inline std::string_view name(CoffeeType t) {
    switch (t) {
        case CoffeeType::Espresso:   return "Espresso";
        case CoffeeType::Cappuccino: return "Cappuccino";
        case CoffeeType::Americano:  return "Americano";
        case CoffeeType::Latte:      return "Latte";
    }
    return "Unknown";
}

inline std::string_view name(CupSize s) {
    switch (s) {
        case CupSize::Small:  return "Small";
        case CupSize::Medium: return "Medium";
        case CupSize::Large:  return "Large";
    }
    return "Unknown";
}

} // namespace coffee
