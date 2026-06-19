#include <FactoryMethodPattern_classic/CircleCreator.hpp>
#include <FactoryMethodPattern_classic/RectangleCreator.hpp>
#include <FactoryMethodPattern_classic/TriangleCreator.hpp>

#include <iostream>
#include <memory>
#include <vector>

int main()
{
    using namespace factory_method_pattern_classic;

    const std::vector<std::unique_ptr<ShapeCreator>> creators = [] {
        std::vector<std::unique_ptr<ShapeCreator>> result;
        result.push_back(std::make_unique<CircleCreator>());
        result.push_back(std::make_unique<RectangleCreator>());
        result.push_back(std::make_unique<TriangleCreator>());
        return result;
    }();

    for (const auto& creator : creators) {
        creator->render_preview(std::cout);
    }
}
