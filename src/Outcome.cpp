#include "Outcome.hpp"
#include "util.hpp"

/* ****** Outcome ****** */
Outcome::Outcome() : menuState_(MenuState::none) {
    menuButton_ = new InteractiveButton("Back to menu", sf::Vector2f(350, 80), sf::Vector2f(0.5f, 0.4f), &menuState_, MenuState::index, sf::Vector2f(0, 200));
}

Outcome::~Outcome() { 
    delete menuButton_;
}

void Outcome::Create(sf::Vector2u window_size) {
    screen_size_ = sf::Vector2u(window_size.x, window_size.y);
    canvas_.create(window_size.x, window_size.y);
}

void Outcome::Initialize() {
    menuState_ = MenuState::none;
    message_ = "";
}

void Outcome::SetState(bool outcome, std::string message) {
    state_ = outcome;
    if (state_) {
        title_ = "You won";
    }
    else {
        title_ = "Game over";
    }
    message_ = message;
}

void Outcome::Resize(unsigned x, unsigned y) {
    // Update size, recreate canvas
    screen_size_ = sf::Vector2u(x, y);
    canvas_.create(x, y);
}

void Outcome::Update(sf::Vector2i mouse, bool clicked) {
    menuButton_->Update(mouse, clicked);
}

MenuState Outcome::GetState() {
    return menuState_;
}

sf::Sprite Outcome::GetSprite() {
    canvas_.clear(sf::Color::Transparent);

    // Title text
    auto title = CreateCenteredText(title_, sf::Vector2f(0.5f * float(screen_size_.x), 0.25f * float(screen_size_.y)), 60, sf::Color::White);
    canvas_.draw(title);
    // Message text contains information how the game ended
    auto text = CreateCenteredText(message_, sf::Vector2f(0.5f * float(screen_size_.x), 0.4f * float(screen_size_.y)), 24, sf::Color::White);
    canvas_.draw(text);

    // Back to menu button
    canvas_.draw(menuButton_->getSprite(screen_size_));

    canvas_.display();

    // Generate sprite and return
    texture_ = canvas_.getTexture();
    sprite_ = sf::Sprite(texture_);
    sprite_.setOrigin(texture_.getSize().x, texture_.getSize().y);
    sprite_.setPosition(screen_size_.x/2, screen_size_.y/2);
    return sprite_;
}
