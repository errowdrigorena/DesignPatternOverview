#pragma once

#include <iosfwd>
#include <string>
#include <vector>

namespace prototype_pattern_classic
{
    class Prototype
    {
    public:
        virtual ~Prototype() = default;

        [[nodiscard]] virtual Prototype* clone() const = 0;
        virtual void set_name(std::string name) = 0;
        virtual void set_scale(double scale) = 0;
        virtual void add_layer(std::string layer_name) = 0;
        virtual void draw(std::ostream& output) const = 0;
    };

    class UiCardPrototype final : public Prototype
    {
    public:
        UiCardPrototype(std::string name, double scale);

        [[nodiscard]] UiCardPrototype* clone() const override;
        void set_name(std::string name) override;
        void set_scale(double scale) override;
        void add_layer(std::string layer_name) override;
        void draw(std::ostream& output) const override;

    private:
        std::string name_;
        double scale_;
        std::vector<std::string> layers_;
    };
}  // namespace prototype_pattern_classic
