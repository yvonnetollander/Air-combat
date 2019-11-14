#include <cmath>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include "globals.hpp"

ScrollingBackdrop::ScrollingBackdrop(const std::string spritepath, const float velocity, const float static_velocity = 0.f)
    : MovingEntity(sf::Vector2f(), spritepath, 0, false), velocity_(velocity), static_velocity_(static_velocity), view_velocity_()
{
    setOrigin(sf::Vector2f(0, 0));
    // Repeat sprite two times to the right, we will later move one full width
    // to the left to have one repeat on each side
    setRepeated(true);
    setTextureRect(sf::IntRect(0, 0, getSize().x * 3, getSize().y));
}

void ScrollingBackdrop::act(float dt, std::vector<MovingEntity*> moving_entities) {
    // Movement relative to v
    const float dx = velocity_ * view_velocity_.x * movement_scale_.x * dt;
    // Static movement
    const float static_dx = static_velocity_ * movement_scale_.x * dt;
    // Move & clip back to original position when we go over a full width
    sf::Vector2f pos = getPos();
    setPos(sf::Vector2f(std::fmod(pos.x - dx - static_dx, getSize().x * movement_scale_.x), pos.y));
}

void ScrollingBackdrop::setViewVelocity(sf::Vector2f v) {
    view_velocity_ = v;
}

void ScrollingBackdrop::setMovementScale(sf::Vector2f s) {
    movement_scale_ = s;
}

Background::Background(const sf::Vector2u size)
    : size_(size), scale_({1.f, 1.f}), repeats_(1u), blend_color_(sf::Color::Black) {}

Background::~Background() {
    for(auto entity : backdrops_)
        delete entity;
}

void Background::setScale(sf::Vector2f scale) {
    scale_ = scale;
    render_texture_.create(size_.x * scale_.x, size_.y * scale_.y);
    for(auto entity : backdrops_)
        entity->setMovementScale(scale_);
}

void Background::setRepetition(unsigned repeats) {
    repeats_ = repeats;
}

void Background::setBlendColor(sf::Color color) {
    blend_color_ = color;
}

void Background::addBackdrop(ScrollingBackdrop* backdrop) {
    backdrop->setMovementScale(scale_);
    backdrops_.push_back(backdrop);
}

void Background::update(sf::Vector2f v, const float dt) {
    for(auto& entity : backdrops_) {
        entity->setViewVelocity(v);
        entity->act(dt, std::vector<MovingEntity*>());
    }
}

const sf::Sprite Background::getTexture() {
    render_texture_.clear(sf::Color::Transparent);

    // Draw backdrops
    for(auto& entity : backdrops_) {
        auto transform = entity->getTransform();
        auto sprite = entity->getSprite();
        sprite.setScale(scale_);
        // Additionally translate one full width to the left
        render_texture_.draw(sprite, sf::RenderStates(transform.translate(-scale_.x * size_.x, 0)));
    }
    render_texture_.display();
    texture_ = render_texture_.getTexture();

    // Apply repetition
    texture_.setRepeated(true);
    sprite_ = sf::Sprite(texture_);
    sprite_.setTextureRect(sf::IntRect(0, 0, texture_.getSize().x * repeats_, texture_.getSize().y));

    return sprite_;
}

 const sf::Transform Background::getTransform() const {
     return transform_;
 }

void Background::fitToScreen(const sf::Vector2u base_size, const float zoom, const float margin = 0.f) {
    // Compute the repetitions we need to fit the screen, again taking
    // into account scaling
    const unsigned repetitions = ((float) base_size.x / (float) size_.x / zoom) + 1 ;
    // Apply both
    setScale(sf::Vector2f(zoom, zoom));
    setRepetition(repetitions);
    // Align to bottom
    transform_ = sf::Transform().translate(0, base_size.y - (size_.y * zoom) - margin);
}

// Example backgrounds
// Credits for the original sprites to ansimuz at opengameart :)
// Some were edited mostly to properly loop and fit the same size
const Background duskMountainBackground() {
    Background bg = Background(sf::Vector2u(272,160));
    bg.addBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/parallax-mountain-bg.png", 0, -10));
    bg.addBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/parallax-mountain-montain-far.png", 22));
    bg.addBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/parallax-mountain-mountains.png", 35));
    bg.addBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/parallax-mountain-trees.png", 55));
    bg.addBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/parallax-mountain-foreground-trees.png", 80));
    bg.setBlendColor(sf::Color(171, 106, 140));
    bg.fitToScreen(sf::Vector2u(2904, 1635), 4);
    return bg;
}
