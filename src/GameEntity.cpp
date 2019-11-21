#include <iostream>
#include "GameEntity.hpp"

GameEntity::GameEntity() :
    pos_(), sprite_(), rotation_(0.0f), dead_(false) {}

GameEntity::GameEntity(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d) : 
    pos_(p), rotation_(r), dead_(d) {
    if (!texture_.loadFromFile(spritepath))
        std::cerr << "Failed to load texture: " << spritepath << std::endl;
    else {
        sprite_.setTexture(texture_);
        sprite_.setOrigin(texture_.getSize().x/2, texture_.getSize().y/2);
    }
}

void GameEntity::SetScale(const sf::Vector2f scale) {
    sprite_.setScale(scale);
}

const sf::Vector2f GameEntity::getPos() const {
    return pos_;
}

const sf::Vector2u GameEntity::getSize() const {
    return texture_.getSize();
}

const sf::Sprite& GameEntity::getSprite() const {
    return sprite_;
}

const sf::Transform GameEntity::getTransform() const {
    sf::Transform transform;
    transform.translate(pos_).rotate(rotation_);
    return transform;
}

void GameEntity::setPos(const sf::Vector2f& p) {
    pos_ = p;
}

const bool GameEntity::isDead() const {
    return dead_;
}

void GameEntity::setRepeated(bool val) {
    texture_.setRepeated(val);
}

void GameEntity::setOrigin(sf::Vector2f origin) {
    sprite_.setOrigin(origin);
}

 void GameEntity::setTextureRect(sf::IntRect r) {
     sprite_.setTextureRect(r);
 }

void GameEntity::kill() {
    dead_ = true;
}

void GameEntity::Rotate(const float deg) {
    rotation_ += deg;
}

void GameEntity::SetRotation(const float deg) {
    rotation_ = deg;
}
