#include "MovingEntity.hpp"

MovingEntity::MovingEntity()
    : GameEntity() {}

MovingEntity::MovingEntity(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d)
    : GameEntity(p, spritepath, r, d) { velocity_ = v; }

void MovingEntity::act(float dt) { 
    Move(dt);
}

void MovingEntity::act(float dt, Engine& engine) {
    Move(dt);
}

void MovingEntity::Move(float dt) {
    setPos(pos_ + velocity_ * dt);
}

const sf::Vector2f MovingEntity::getVelocity() const {
    return velocity_;
}