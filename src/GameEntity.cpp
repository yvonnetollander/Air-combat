#include <iostream>
#include "GameEntity.hpp"

GameEntity::GameEntity() :
    pos_(), sprite_(), rotation_(0.0f), dead_(false) {}

GameEntity::GameEntity(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d) : 
    pos_(p), rotation_(r), dead_(d)
    {
        if (!texture_.loadFromFile(spritepath))
            std::cerr << "Failed to load texture: " << spritepath << std::endl;
        else {
            sprite_.setTexture(texture_);
            sprite_.setOrigin(texture_.getSize().x/2, texture_.getSize().y/2);
        }
    }

const sf::Vector2f GameEntity::getPos() const {
    return pos_;
}

const sf::Sprite GameEntity::getSprite() const {
    return sprite_;
}

const sf::Transform GameEntity::getTransform() const {
    sf::Transform transform;
    transform.translate(pos_).rotate(rotation_);
    return transform;
}

void GameEntity::SetPos(const sf::Vector2f& p) {
    pos_ = p;
}

const bool GameEntity::isDead() const {
    return dead_;
}

void GameEntity::kill() {
    dead_ = true;
}
