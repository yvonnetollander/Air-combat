#pragma once

#include <SFML/Graphics.hpp>
#include "MovingEntity.hpp"
#include "Troop.hpp"
/*
    Class Minimap represents a minimap UI element
*/
class Minimap {
public:
    Minimap();
    // Get sprite to be drawn
    const sf::Sprite GetSprite(std::vector<MovingEntity*>& entities, std::vector<Troop*>& enemies);
    // Align minimap to a given screen size
    void Align(unsigned x, unsigned y);
    // Align minimap scale to a given world size
    void SetWorldSize(int x, int y);
    // Transform world coordinates to local minimap coordinates
    sf::Vector2f TransformWorldToMap(sf::Vector2f vec);
    // Draw a dot on the minimap based on world coordinates
    void DrawOnMap(sf::Vector2f pos, const float size);
    // Update camera state
    void SetCamera(sf::View camera);
private:
    // Canvas size (in pixels, pre-scaling)
    // Only set x values matters, y is set based on world aspect ratio
    sf::Vector2f size_;
    // Screen-relative padding from bottom right corner
    sf::Vector2f padding_ = sf::Vector2f(-10, 1990);
    // Screen size / minimap anchor point
    sf::Vector2f anchor_;
    
    sf::Vector2f worldsize_;
    sf::View camera_;
    sf::RenderTexture render_texture_;
    sf::RectangleShape background_;
    sf::Texture t_;
    sf::Sprite s_;
};