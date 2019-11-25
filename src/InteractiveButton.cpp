#include "InteractiveButton.hpp"
#include "util.hpp"
#include <iostream>

InteractiveButton::InteractiveButton(std::string string, sf::Vector2f size, sf::Vector2f center, MenuState* state, MenuState to_set, sf::Vector2f offset)
        : size_(size),
        center_(center),
        state_(state),
        to_set_(to_set),
        offset_(offset),
        rect_(sf::Vector2f(size_.x, size_.y)),
        text_(CreateCenteredText(string, center, 20, sf::Color::White))
    { canvas_.create(size.x, size.y); }

void InteractiveButton::Update(sf::Vector2i mouse, bool clicked) {
    hover_ = Contains(mouse);
    if (hover_ && clicked && state_)
        *state_ = to_set_;
}

sf::Sprite InteractiveButton::getSprite(sf::Vector2u screen) {
    screen_ = screen;
    const sf::Color color = sf::Color::Blue;

    rect_.setFillColor(hover_ ? Lighter(color) : color);
    CenterText(text_, sf::Vector2f(size_.x/2.f, size_.y/2.f));

    canvas_.clear(sf::Color::Red);
    canvas_.draw(rect_);
    canvas_.draw(text_);
    canvas_.display();

    texture_ = canvas_.getTexture();
    sprite_ = sf::Sprite(texture_);
    sprite_.setOrigin(size_.x/2.f, size_.y/2.f);
    sprite_.setPosition(center_.x * screen_.x + offset_.x, center_.y * screen_.y + offset_.y);
    return sprite_;
}

const bool InteractiveButton::Contains(sf::Vector2i coords) const {
    float left = center_.x * screen_.x + offset_.x - size_.x / 2.f;
    float top = center_.y * screen_.y + offset_.y - size_.y / 2.f;
    return coords.x > left && coords.x < left+size_.x && coords.y > top && coords.y < top+size_.y;
}
