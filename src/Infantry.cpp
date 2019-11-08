#include "Infantry.hpp"
#include "util.cpp"
#include <stdlib.h>
#include <algorithm>

Infantry::Infantry() :
    Troop(), velocity_(0), targetPos_(), wanderRadius_(0), idle_(0) { pickTarget(); }

Infantry::Infantry(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d, const unsigned hp, const float v, const float radius) : 
    Troop(p, t, r, d, hp), velocity_(v), wanderRadius_(radius), idle_(0) { pickTarget(); }

void Infantry::act(float dt) {
    sf::Vector2f diff = targetPos_ - getPos();
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

void Infantry::pickTarget() {
    float random = randFloat();
    // Currently only moves on the x-axis
    targetPos_ = sf::Vector2f(2.0f * (random - 0.5f) * wanderRadius_, 0);
}

void Infantry::fire() {
    // pew pew
}