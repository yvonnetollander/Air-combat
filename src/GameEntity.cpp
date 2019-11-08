#include "GameEntity.hpp"

GameEntity::GameEntity() :
    pos_(), sprite_(), rotation_(0.0f), dead_(false) {}

GameEntity::GameEntity(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d) : 
        pos_(p), sprite_(t), rotation_(r), dead_(d) {}

const sf::Vector2f GameEntity::getPos() const {
    return pos_;
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
