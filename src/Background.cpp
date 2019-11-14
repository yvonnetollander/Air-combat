#include <cmath>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include "globals.hpp"

ScrollingBackdrop::ScrollingBackdrop(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const float velocity)
    : MovingEntity(p, spritepath, r, d), velocity_(velocity), view_velocity_()
    {
        setRepeated(true);
        setTextureRect(sf::IntRect(0, 0, getSize().x * 2, getSize().y));
    }

void ScrollingBackdrop::act(float dt, std::vector<MovingEntity*> moving_entities) {
    float dx = velocity_ * view_velocity_.x * movement_scale_.x * dt;
    sf::Vector2f pos = getPos();
    setPos(sf::Vector2f(std::fmod(pos.x - dx, getSize().x * movement_scale_.x), pos.y));
}

void ScrollingBackdrop::setViewVelocity(sf::Vector2f v) {
    view_velocity_ = v;
}

void ScrollingBackdrop::setMovementScale(sf::Vector2f s) {
    movement_scale_ = s;
}

Background::~Background() {
    for(auto entity : backdrops_)
        delete entity;
}

void Background::setProportions(sf::Vector2u size, sf::Vector2f scale, sf::Vector2f offset = sf::Vector2f()) {
    scale_ = scale;
    size_ = size;
    offset_ = sf::Vector2f(offset.x * scale_.x, offset_.y * scale_.y);
    render_texture_.create(size.x * scale_.x, size.y * scale_.y);
    for(auto entity : backdrops_)
        entity->setMovementScale(scale_);
}

void Background::addBackdrop(ScrollingBackdrop* backdrop) {
    backdrop->setMovementScale(scale_);
    backdrop->setPos(sf::Vector2f(backdrop->getPos().x * scale_.x, backdrop->getPos().y * scale_.y));
    backdrops_.push_back(backdrop);
}

void Background::update(const sf::Vector2f v, const float dt) {
    for(auto& entity : backdrops_) {
        entity->setViewVelocity(v);
        entity->act(dt, std::vector<MovingEntity*>());
    }
}

const sf::Sprite Background::GetTexture() {
    render_texture_.clear();
    for(auto& entity : backdrops_) {
        auto transform = entity->getTransform();
        auto sprite = entity->getSprite();
        sprite.setScale(scale_);
        render_texture_.draw(sprite, sf::RenderStates(transform.translate(offset_)));
    }
    render_texture_.display();

    texture_ = render_texture_.getTexture();
    sprite_ = sf::Sprite(texture_);
    return sprite_;
}

const Background duskMountainBackground() {
    Background bg;
    bg.setProportions(sf::Vector2u(272,160), sf::Vector2f(8, 8), sf::Vector2f(136, 0));
    bg.addBackdrop(new ScrollingBackdrop(sf::Vector2f(0, 80), ROOTDIR + "/res/parallax-mountain-bg.png", 0, false, 0));
    bg.addBackdrop(new ScrollingBackdrop(sf::Vector2f(0, 80), ROOTDIR + "/res/parallax-mountain-montain-far.png", 0, false, 20));
    bg.addBackdrop(new ScrollingBackdrop(sf::Vector2f(0, 80), ROOTDIR + "/res/parallax-mountain-mountains.png", 0, false, 35));
    bg.addBackdrop(new ScrollingBackdrop(sf::Vector2f(0, 80), ROOTDIR + "/res/parallax-mountain-trees.png", 0, false, 55));
    bg.addBackdrop(new ScrollingBackdrop(sf::Vector2f(0, 80), ROOTDIR + "/res/parallax-mountain-foreground-trees.png", 0, false, 80));
    return bg;
}
