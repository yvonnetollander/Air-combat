#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

/* Class head-up display alias HUD.
*  Tracks players hitpoints, enemies, weapon and ammo count.
*/
class HUD {
public:
    HUD();
    ~HUD() {}
    HUD& operator=(const HUD& hud);
    // Create backgroung
    void Create(const sf::Vector2f size);
    // Get sprite to be drawn
    const sf::Sprite GetSprite();
    // Update changing player values
    void UpdateValues(const unsigned hp, const unsigned enemies, const unsigned ammo);
    // Update text to match updated values
    void UpdateTexts();
    // TODO: Resize the HUD when screen size is changed
    void Resize(const float base_width, const float base_height);

    const sf::Transform GetTransform() const;

private:
    // Canvas size (in pixels, pre-scaling)
    sf::Vector2f size_;
    sf::Transform transform_;

    sf::RenderTexture render_texture_;
    sf::RectangleShape background_;
    sf::Texture t_;
    sf::Sprite s_;
    sf::Font font;
    sf::Text text_[4];
    
    unsigned max_hp_;
    unsigned hp_;
    unsigned total_enemies_;
    unsigned enemies_;
    unsigned total_ammo_;
    unsigned ammo_;
};
