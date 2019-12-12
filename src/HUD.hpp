#pragma once

#include <SFML/Graphics.hpp>

#include "globals.hpp"

/*  Class head-up display alias HUD.
    A HUD displayes the state of the game and different variables.
    The HUD displays:
        players current health points and maximum health points
        the amount of enemies left and the inital enemy count in the beginning of the game
        the weapon player has
        how many ammos the player has left and the maximum amount.
    The HUD is updated during the game and displayes current state.
*/
class HUD {
public:
    HUD();
    ~HUD() {}
    HUD& operator=(const HUD& hud);
    // Create backgroung for HUD
    void Create(const sf::Vector2f size);
    // Get sprite to be drawn
    const sf::Sprite GetSprite();
    // Initialize max values and set current values to the maximum
    void InitializeValues(const unsigned hp, const unsigned enemies, const unsigned ammo, std::string weapon);
    // Update changing player values
    void UpdateValues(const unsigned hp, const unsigned enemies, const unsigned ammo);
    // Update text to match updated values
    void UpdateTexts();
    // Resize the HUD when screen size is changed
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
    // Information showed in hud
    sf::Text text_[4];
    
    // Players maximum hp
    unsigned max_hp_;
    // Players current hp
    unsigned hp_;
    // Total amount of enemies in the beginning of the game
    unsigned total_enemies_;
    // Current amount of enemies left
    unsigned enemies_;
    // Players mamimum ammo count
    unsigned total_ammo_;
    // How many ammos player has left
    unsigned ammo_;
    // Description/name of the weapon player uses
    std::string weapon_;
};
