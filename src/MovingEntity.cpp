#include "MovingEntity.hpp"

MovingEntity::MovingEntity()
    : GameEntity() {}

MovingEntity::MovingEntity(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d)
    : GameEntity(p, spritepath, r, d) { velocity_ = v; }

void MovingEntity::Move(float dt) {
    SetPos(pos_ + velocity_ * dt);
}