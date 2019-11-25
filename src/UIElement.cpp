#include "UIElement.hpp"

InteractiveButton::InteractiveButton(sf::Vector2f size, sf::Vector2f center, bool& flag, sf::Vector2f offset)
    : size_(size), center_(center), flag_(flag), offset_(offset)
    { canvas_.create(size.x, size.y); }

void InteractiveButton::Update(sf::Vector2i mouse) {
    hover_ = Contains(mouse);
}

sf::Sprite InteractiveButton::getSprite(sf::Vector2u screen) {
    screen_ = screen;
    const sf::Color color = sf::Color::Blue;

    auto button = sf::RectangleShape(sf::Vector2f(size_.x, size_.y));
    button.setFillColor(hover_ ? Lighter(color) : color);

    canvas_.clear(sf::Color::Red);
    canvas_.draw(button);
    canvas_.display();

    texture_ = canvas_.getTexture();
    sprite_ = sf::Sprite(texture_);
    sprite_.setOrigin(size_.x/2.f, size_.y/2.f);
    sprite_.setPosition(center_.x * screen_.x + offset_.x, center_.y * screen_.y + offset_.y);
    return sprite_;
}

bool InteractiveButton::Contains(sf::Vector2i coords) {
    float left = center_.x * screen_.x + offset_.x - size_.x / 2.f;
    float top = center_.y * screen_.y + offset_.y - size_.y / 2.f;
    return coords.x > left && coords.x < left+size_.x && coords.y > top && coords.y < top+size_.y;
}
