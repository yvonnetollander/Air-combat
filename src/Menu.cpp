#include <iostream>

#include "Menu.hpp"
#include "util.hpp"
#include "globals.hpp"

Menu::Menu() : done_(false) {
    bool kek = true;
    buttons_.push_back(new InteractiveButton(sf::Vector2f(350, 100), sf::Vector2f(0.5f, 0.5f), kek));
    buttons_.push_back(new InteractiveButton(sf::Vector2f(350, 100), sf::Vector2f(0.5f, 0.5f), kek, sf::Vector2f(0, 120)));
    buttons_.push_back(new InteractiveButton(sf::Vector2f(350, 100), sf::Vector2f(0.5f, 0.5f), kek, sf::Vector2f(0, 240)));
}

void Menu::Create(Config* config, sf::Vector2u window_size) {
    config_ = config;
    screen_size_ = sf::Vector2u(window_size.x, window_size.y);
    canvas_.create(window_size.x, window_size.y);
}

void Menu::Update(sf::Vector2i mouse) {
    for (auto& button : buttons_)
        button->Update(mouse);
}

void Menu::Resize(unsigned x, unsigned y) {
    // Make sure we maintain correct positioning
    offset_ += (sf::Vector2f(screen_size_.x, screen_size_.y) - sf::Vector2f(x,y)) / 2.f;
    // Update size, recreate canvas
    screen_size_ = sf::Vector2u(x, y);
    canvas_.create(x, y);
}

sf::Sprite Menu::getSprite() {
    auto title = CreateCenteredText("Air Combat", sf::Vector2f(0.5f * float(screen_size_.x), 0.3f * float(screen_size_.y)), 20, sf::Color::Red);
    title.setFont(AirCombatFonts::roboto_regular);

    bool kek = true;

    canvas_.clear(sf::Color::Black);
    canvas_.draw(title);

    for (auto& button : buttons_)
        canvas_.draw(button->getSprite(screen_size_));

    canvas_.display();

    texture_ = canvas_.getTexture();
    sprite_ = sf::Sprite(texture_);
    sprite_.setPosition(offset_);
    return sprite_;
}
