#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
/*
    Class InteractiveButton represents a simple UI button with on-hover effects
    On click, sets param state_ to param to_set
*/
class InteractiveButton {
public:
    InteractiveButton(const InteractiveButton&) {}
    InteractiveButton(std::string string, sf::Vector2f size, sf::Vector2f center, MenuState* state_, MenuState to_set, sf::Vector2f offset = sf::Vector2f());
    // Update hover animation based on mouse
    void Update(sf::Vector2i mouse, bool clicked);
    // Check if a given point is within the button bounds
    const bool Contains(sf::Vector2i coords) const;
    sf::Sprite getSprite(sf::Vector2u screen);
private:
    // Screen size
    sf::Vector2u screen_;
    // Button size
    sf::Vector2f size_;
    // Center position
    sf::Vector2f center_;

    MenuState* state_;
    MenuState to_set_;

    // Position offset
    sf::Vector2f offset_;
    // Hover flag
    bool hover_;
    // Drawing elements
    sf::RectangleShape rect_;
    sf::Text text_;
    sf::RenderTexture canvas_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};
