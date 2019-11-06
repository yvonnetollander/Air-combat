#include "GameEntity.hpp"

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
