#include "GameEntity.hpp"

GameEntity::GameEntity() :
    pos_(0.0f, 0.0f, 0.0f), sprite_(), rotation_(0.0f), dead_(false) {}

GameEntity::GameEntity(const sf::Vector3f& p, const sf::Texture& t, const float r, const bool d) : 
        pos_(p), sprite_(t), rotation_(r), dead_(d) {}

const sf::Vector3f GameEntity::getPos() const {
    return pos_;
}

void GameEntity::SetPos(const sf::Vector3f& p) {
    pos_ = p;
}

const bool GameEntity::isDead() const {
    return dead_;
}

void GameEntity::kill() {
    dead_ = true;
}
