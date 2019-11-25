#include <iostream>

#include "Menu.hpp"
#include "util.hpp"
#include "globals.hpp"

Menu::Menu() : state_(MenuState::index) {
    buttons_.push_back(new InteractiveButton("Play", sf::Vector2f(350, 80), sf::Vector2f(0.5f, 0.4f), &state_, MenuState::play));
    buttons_.push_back(new InteractiveButton("Settings?", sf::Vector2f(350, 80), sf::Vector2f(0.5f, 0.4f), &state_, MenuState::index, sf::Vector2f(0, 100)));
    buttons_.push_back(new InteractiveButton("Credits?", sf::Vector2f(350, 80), sf::Vector2f(0.5f, 0.4f), &state_, MenuState::index, sf::Vector2f(0, 200)));
    buttons_.push_back(new InteractiveButton("Exit", sf::Vector2f(350, 80), sf::Vector2f(0.5f, 0.4f), &state_, MenuState::quit, sf::Vector2f(0, 300)));
}

Menu::~Menu() {
    for (auto& button : buttons_)
        delete button;
}

void Menu::Create(Config* config, sf::Vector2u window_size) {
    config_ = config;
    screen_size_ = sf::Vector2u(window_size.x, window_size.y);
    canvas_.create(window_size.x, window_size.y);
}

void Menu::Update(sf::Vector2i mouse, bool clicked) {
    for (auto& button : buttons_)
        button->Update(mouse, clicked);
}

void Menu::Resize(unsigned x, unsigned y) {
    // Update size, recreate canvas
    screen_size_ = sf::Vector2u(x, y);
    canvas_.create(x, y);
}

MenuState Menu::GetState() {
    return state_;
}

sf::Sprite Menu::GetSprite() {
    canvas_.clear(sf::Color::Transparent);

    // Title text
    auto title = CreateCenteredText("Air Combat", sf::Vector2f(0.5f * float(screen_size_.x), 0.25f * float(screen_size_.y)), 60, sf::Color::White);
    canvas_.draw(title);

    // Buttons
    for (auto& button : buttons_)
        canvas_.draw(button->getSprite(screen_size_));

    canvas_.display();

    // Generate sprite and return
    texture_ = canvas_.getTexture();
    sprite_ = sf::Sprite(texture_);
    sprite_.setOrigin(texture_.getSize().x, texture_.getSize().y);
    sprite_.setPosition(screen_size_.x/2, screen_size_.y/2);
    return sprite_;
}
