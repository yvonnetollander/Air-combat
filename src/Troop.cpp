#include "Troop.hpp"
#include "util.cpp"
#include <stdlib.h>
#include <algorithm>

Troop::Troop() :
    MovingEntity(), velocity_(0), targetPos_(), wanderRadius_(0), idle_(0) { pickTarget(); }

Troop::Troop(const sf::Vector3f& p, const sf::Texture& t, const float r, const bool d, const float v, const float radius) : 
    MovingEntity(p, t, r, d), velocity_(v), wanderRadius_(radius), idle_(0) { pickTarget(); }

void Troop::act(float dt) {
    sf::Vector3f diff = targetPos_ - getPos();
    float movement = velocity_ * dt;
    if(idle_ > 0) {
        idle_ = std::max(0.0f, idle_ - dt)
    }
    else {
        if(len(diff) < movement) {
            SetPos(targetPos_);
            idle_ = randFloat() * 5.0f;
        }
        else {
            SetPos(getPos() + normalize(diff) * movement);
        }
    }
}

void Troop::pickTarget() {
    float random = randFloat();
    // Currently only moves on the x-axis
    targetPos_ = sf::Vector3f(2.0f * (random - 0.5f) * wanderRadius_, 0 ,0);
}
