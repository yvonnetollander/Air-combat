#include <stdlib.h>
#include <algorithm>
#include "Infantry.hpp"
#include "util.hpp"

/* ****** Infantry ****** */
Infantry::Infantry()
    : Troop(), targetPos_(), idle_(0), wanderRadius_(0) { pickTarget(); }

Infantry::Infantry(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, const float radius, unsigned ammo_left)
    : Troop(p, sf::Vector2f(0.5f, 0.0f), spritepath, r, d, hp, ammo_left), targetPos_(), idle_(0), wanderRadius_(radius) { pickTarget(); }

void Infantry::Act(float dt, std::vector<MovingEntity*> moving_entities, const sf::Vector2f& player_pos, 
        const sf::Vector2f& player_velocity) {
    if (!dead_) {
        sf::Vector2f diff = targetPos_ - getPos();
        float movement = velocity_.x * dt;
        // If Infantry is idle, decrease the remaining time
        if(idle_ > 0) {
            idle_ = std::max(0.0f, idle_ - dt);
        }
        // If infantry is not idle change its position
        else {
            // If the Infantry can reach the target position, it moves to the target position and it is set to be idle for random time
            if(len(diff) < movement) {
                setPos(targetPos_);
                idle_ = randFloat() * 5.0f;
                pickTarget();
            }
            // Otherwise, the infantry moves closer to target position
            else {         
                setPos(getPos() + normalize(diff) * movement);
            }
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
