#include "MovingEntity.hpp"

MovingEntity::MovingEntity()
    : GameEntity(), velocity_() { }

MovingEntity::MovingEntity(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d)
    : GameEntity(p, spritepath, r, d), x_multiplier_(1) { velocity_ = v; }

Projectile* MovingEntity::Act(float dt) { 
    Move(dt);
    return nullptr;
}

void MovingEntity::Move(float dt) {
    setPos(pos_ + velocity_ * dt);
}

const sf::Vector2f MovingEntity::getVelocity() const {
    return velocity_;
}

void MovingEntity::FlipX() {
    x_multiplier_ = -x_multiplier_;
    SetScale(sf::Vector2f(1.f * x_multiplier_, 1.f));
}
