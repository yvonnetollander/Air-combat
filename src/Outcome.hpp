#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>
#include "InteractiveButton.hpp"
#include "globals.hpp"

/*  Outcome is a class that represents the result of the game. 
    state_ is true if the player won the game and false if the player lost */
class Outcome {
public:
    Outcome();
    ~Outcome();
    void Create(sf::Vector2u window_size);
    // Resize to a window
    void Resize(unsigned x, unsigned y);
    // Initialize values
    void Initialize();
    // Update state/logic
    void Update(sf::Vector2i mouse, bool clicked);
    // If a player wins the game set the state true, otherwise false
    void SetState(bool outcome);
    MenuState GetState();
    sf::Sprite GetSprite();
private:
    bool state_;
    std::string title_;
    sf::Vector2u screen_size_;

    MenuState menuState_;
    // Back to menu from settings page button
    InteractiveButton *menuButton_;

    // Drawing elements
    sf::RenderTexture canvas_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};
