#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "MovingEntity.hpp"
#include "Projectile.hpp"

/**
    class ScrollingBackdrop depresents a dynamically scrolling backdrop element
    Used as a basic building block in class Background
    Constructor takes in a path to a sprite, a velocity multiplier and a constant velocity
*/
class ScrollingBackdrop : public MovingEntity {
public:
    ScrollingBackdrop(const std::string spritepath, const float velocity, const float static_velocity);
    Projectile* Act(float dt);
    void SetViewVelocity(sf::Vector2f v);
    void SetMovementScale(sf::Vector2f s);
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

    Constructor takes in an uint vector representing the base image size.
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
    // Set up correct texture repetition matching current base window/rect
    void CorrectRepetition();
    // Add new backdrop element (drawn in the order added)
    void AddBackdrop(ScrollingBackdrop* backdrop);
    // Configure background for a given base window/rect
    // And set up the desired scale
    void FitToScreen(const sf::Vector2u base_size, const float scale, const float height);
    // Realign to a new camera center position with the current base window/rect,
    void Recenter(const sf::Vector2f camera_center);
    // Set up correct texture repetition and align to the bottom with the given offset
    void Resize(const float base_width, const float base_height);
    // Update parallax state
    void Update(const sf::Vector2f v, const float dt);
    // Move with the given offset, to keep u with camera/align
    void Move(const float w, const float h);
    // Generate and return a new texture based on the current state
    const sf::Sprite GetTexture();
    const sf::Transform GetTransform() const;
    void SetBlendColor(const sf::Color color);
    const sf::Color GetBlendColor() const;
    void SetScale(const sf::Vector2f scale);
    void SetRepetition(const unsigned repeats);
    const sf::Vector2f GetPos();
    const sf::Vector2f GetScale();
    const sf::Vector2u GetBaseSize();
    const float GetHeightOffset();
private:
    // Scrolling textures
    std::vector<ScrollingBackdrop*> backdrops_;
    // Canvas size (in pixels, pre-scaling)
    const sf::Vector2u size_;
    // Dimensions of the screen we are fitting to
    sf::Vector2u base_size_;
    // Scaling factor
    sf::Vector2f scale_;
    // Repeats of background on the x axis
    unsigned repeats_;
    // Background position
    sf::Vector2f pos_;
    // Background vertical offset
    float height_offset_;
    // Canvas
    sf::RenderTexture render_texture_;
    // Final texture resulting from the canvas
    sf::Texture texture_;
    // Final sprite that gets sent as the background
    sf::Sprite sprite_;
    // The alignment transform for the final sprite. Does not apply
    // the background position. Position gets applied on top by
    // getTransform().
    sf::Transform transform_;
    // The color to be used to blend the background
    sf::Color blend_color_;
};

// Example backgrounds
// Credits for the original sprites to ansimuz at opengameart :)
// Some were edited mostly to properly loop and fit the same size
Background* MountainBackground();
Background* IndustrialBackground();
Background* UnderwaterBackground();

// class BackgroundSet acts as a container for backgrounds, allowing for easy switching in-game
class BackgroundSet {
public:
    BackgroundSet();
    ~BackgroundSet();
    // Chnge current background
    void Switch();
    // Get current background
    Background& Current();
private:
    unsigned current_idx_;
    std::vector<Background*> backgrounds_;
};
