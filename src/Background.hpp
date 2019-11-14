#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "MovingEntity.hpp"

/**
    class ScrollingBackdrop depresents a dynamically scrolling backdrop element
    Used as a basic building block in class Background
    Constructor takes in a path to a sprite, a velocity multiplier and a constant velocity
*/
class ScrollingBackdrop : public MovingEntity {
public:
    ScrollingBackdrop(const std::string spritepath, const float velocity, const float static_velocity);
    void act(float dt, std::vector<MovingEntity*> moving_entities);
    void setViewVelocity(sf::Vector2f v);
    void setMovementScale(sf::Vector2f s);
private:
    // Relative velocity multiplier
    float velocity_;
    // A constant velocity that gets applied on top
    float static_velocity_;
    // Current view/player speed to base movements on for parallax effect
    sf::Vector2f view_velocity_;
    // Relative velocity multiplier to account for background scaling
    sf::Vector2f movement_scale_;
};

/**
    class Background represents a parallax background scene.
    Draws ScrollingBackdrops offscreen onto a RenderTexture which it then
    serves with getTexture(). The backdrops move relative to the vector v
    given to update().

    Constructor takes in an int vector representing the base image size.
    ScrollingBackdrops are assumed to be the given size.

    Can be scaled and repeated horizontally using setScale() and setRepetition().
    Scaling is applied on the original RenderTexture (not the resulting texture)
    to maintain smooth movement.

    Can also be automatically fit into a given base resolution with a given
    zoom level using fitToScreen(). Aligns to the bottom of the given base.
*/
class Background {
public:
    Background(const sf::Vector2u size);
    Background(const Background&);
    ~Background();
    void setScale(const sf::Vector2f scale);
    void setRepetition(const unsigned repeats);
    void setBlendColor(const sf::Color color);
    void addBackdrop(ScrollingBackdrop* backdrop);
    void fitToScreen(const sf::Vector2u base_size, const float zoom, const float margin);
    void update(const sf::Vector2f v, const float dt);
    // Generate and return a new texture based on the current state
    const sf::Sprite getTexture();
    const sf::Transform getTransform() const;
private:
    // Scrolling textures
    std::vector<ScrollingBackdrop*> backdrops_;
    // Canvas size (in pixels, pre-scaling)
    const sf::Vector2u size_;
    // Scaling factor
    sf::Vector2f scale_;
    // Repeats of background on the x axis
    unsigned repeats_;
    // Canvas
    sf::RenderTexture render_texture_;
    // Final texture resulting from the canvas
    sf::Texture texture_;
    // Final sprite that gets sent as the background
    sf::Sprite sprite_;
    // The transform for the final sprite. Simply translates to align to
    // the bottom if fitToScreen() was used
    sf::Transform transform_;
    // The color to be used to blend the background
    sf::Color blend_color_;
};

// An example pre-configured Background
const Background duskMountainBackground();
