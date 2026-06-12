#include "Prototype.h"

#include <ostream>
#include <utility>

namespace prototype_pattern_classic
{
    UiCardPrototype::UiCardPrototype(std::string name, const double scale)
        : name_(std::move(name))
        , scale_(scale)
    {
    }

    UiCardPrototype* UiCardPrototype::clone() const
    {
        return new UiCardPrototype(*this);
    }

    void UiCardPrototype::set_name(std::string name)
    {
        name_ = std::move(name);
    }

    void UiCardPrototype::set_scale(const double scale)
    {
        scale_ = scale;
    }

    void UiCardPrototype::add_layer(std::string layer_name)
    {
        layers_.push_back(std::move(layer_name));
    }

    void UiCardPrototype::draw(std::ostream& output) const
    {
        output << "UiCardPrototype{name=" << name_ << ", scale=" << scale_ << ", layers=[";

        for (std::size_t index = 0; index < layers_.size(); ++index) {
            if (index != 0) {
                output << ", ";
            }

            output << layers_[index];
        }

        output << "]}\n";
    }
}  // namespace prototype_pattern_classic
