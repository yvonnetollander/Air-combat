#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>
#include "InteractiveButton.hpp"
#include "globals.hpp"

class Menu {
public:
    Menu();
    ~Menu();
    bool Done();
    // Initializes the menu, to be called before anything else
    void Create(Config* config, sf::Vector2u window_size);
    // Update state/logic
    void Update(sf::Vector2i mouse, bool clicked);
    // Resize to a window
    void Resize(unsigned x, unsigned y);
    MenuState GetState();
    sf::Sprite GetSprite();
private:
    Config* config_;
    MenuState state_;
    sf::Vector2u screen_size_;
    std::vector<InteractiveButton*> buttons_;
    // Drawing elements
    sf::RenderTexture canvas_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};
