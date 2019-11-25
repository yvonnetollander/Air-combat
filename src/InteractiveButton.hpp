#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "globals.hpp"

class InteractiveButton {
public:
    InteractiveButton(const InteractiveButton&) {}
    InteractiveButton(std::string string, sf::Vector2f size, sf::Vector2f center, MenuState* state_, MenuState to_set, sf::Vector2f offset = sf::Vector2f());
    void Update(sf::Vector2i mouse, bool clicked);
    const bool Contains(sf::Vector2i coords) const;
    sf::Sprite getSprite(sf::Vector2u screen);
private:
    sf::Vector2u screen_;
    sf::Vector2f size_;
    sf::Vector2f center_;
    MenuState* state_;
    MenuState to_set_;
    sf::Vector2f offset_;
    bool hover_;
    // Drawing elements
    sf::RectangleShape rect_;
    sf::Text text_;
    sf::RenderTexture canvas_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};
