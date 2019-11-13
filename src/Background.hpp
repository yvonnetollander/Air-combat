#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Background {
public:
    Background();
    void update(const sf::Vector2f& v, const float& dt);
    const sf::Texture& GetTexture();
private:
    // Background image
    sf::Texture sky_tex_;
    sf::Sprite sky_sprite_;
    sf::Transform sky_transform_;
    float sky_scroll_ = 0u;
    // Background mountain
    sf::Texture bg_mountain_tex_;
    sf::Sprite bg_mountain_sprite_;
    sf::Transform bg_mountain_transform_;
    float bg_mountain_scroll_ = 0u;
    // Foreground mountains
    sf::Texture fg_mountain_tex_;
    sf::Sprite fg_mountain_sprite_;
    sf::Transform fg_mountain_transform_;
    float fg_mountain_scroll_ = 0u;
    // Background trees
    sf::Texture bg_tree_tex_;
    sf::Sprite bg_tree_sprite_;
    sf::Transform bg_tree_transform_;
    float bg_tree_scroll_ = 0u;
    // Foreground trees
    sf::Texture fg_tree_tex_;
    sf::Sprite fg_tree_sprite_;
    sf::Transform fg_tree_transform_;
    float fg_tree_scroll_ = 0u;
    // Final canvas texture
    sf::RenderTexture tx_;
};
