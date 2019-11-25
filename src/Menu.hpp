#pragma once
#include "Config.hpp"
#include <SFML/Graphics.hpp>
#include "UIElement.hpp"

class Menu {
public:
    Menu();
    ~Menu() {}
    bool Done();
    void Create(Config* config, sf::Vector2u window_size);
    void Update(sf::Vector2i mouse);
    void Resize(unsigned x, unsigned y);
    sf::Sprite getSprite();
private:
    Config* config_;
    bool done_;
    sf::Vector2u screen_size_;
    // Positional offset to account for screen resize
    sf::Vector2f offset_;
    std::vector<InteractiveButton*> buttons_;
    // Drawing elements
    sf::Font font_;
    sf::RenderTexture canvas_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};
