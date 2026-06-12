#include <PrototypePattern_classic/Prototype.h>

#include <iostream>
#include <memory>

int main()
{
    using prototype_pattern_classic::Prototype;
    using prototype_pattern_classic::UiCardPrototype;

    auto checkout_card = std::make_unique<UiCardPrototype>("checkout-card", 1.0);
    checkout_card->add_layer("background");
    checkout_card->add_layer("price");
    checkout_card->add_layer("primary-button");

    Prototype* highlighted_checkout_card = checkout_card->clone();
    highlighted_checkout_card->set_name("checkout-card-highlighted");
    highlighted_checkout_card->set_scale(1.15);
    highlighted_checkout_card->add_layer("focus-ring");

    checkout_card->draw(std::cout);
    highlighted_checkout_card->draw(std::cout);

    delete highlighted_checkout_card;

    return 0;
}
