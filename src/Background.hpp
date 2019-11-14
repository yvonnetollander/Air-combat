#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "MovingEntity.hpp"

class ScrollingBackdrop : public MovingEntity {
public:
    ScrollingBackdrop(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const float velocity);
    void act(float dt, std::vector<MovingEntity*> moving_entities);
    void setViewVelocity(sf::Vector2f v);
    void setMovementScale(sf::Vector2f s);
private:
    float velocity_;
    sf::Vector2f view_velocity_;
    sf::Vector2f movement_scale_;
};

class Background {
public:
    Background() {}
    Background(const Background&);
    ~Background();
    void setProportions(sf::Vector2u size, sf::Vector2f scale, sf::Vector2f offset);
    void setTextureOffset(sf::Vector2f offset);
    void addBackdrop(ScrollingBackdrop* backdrop);
    void update(const sf::Vector2f v, const float dt);
    const sf::Sprite GetTexture();
private:
    // Scrolling textures
    std::vector<ScrollingBackdrop*> backdrops_;
    // Texture position offset
    sf::Vector2f offset_;
    // Canvas size (in pixels, pre-scaling)
    sf::Vector2u size_;
    // Scaling factor
    sf::Vector2f scale_;
    // Canvas
    sf::RenderTexture render_texture_;
    // Final texture resulting from the canvas
    sf::Texture texture_;
    // Final sprite that gets sent as the background
    sf::Sprite sprite_;
};

const Background duskMountainBackground();
