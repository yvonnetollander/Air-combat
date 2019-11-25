#pragma once

#include "util.hpp"

class InteractiveButton {
public:
    InteractiveButton(const InteractiveButton&) {}
    InteractiveButton(sf::Vector2f size, sf::Vector2f center, bool& flag, sf::Vector2f offset = sf::Vector2f());
    void Update(sf::Vector2i mouse);
    bool Contains(sf::Vector2i coords);
    sf::Sprite getSprite(sf::Vector2u screen);
private:
    sf::Vector2u screen_;
    sf::Vector2f size_;
    sf::Vector2f center_;
    bool flag_;
    sf::Vector2f offset_;
    bool hover_;
    // Drawing elements
    sf::Font font_;
    sf::RenderTexture canvas_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};