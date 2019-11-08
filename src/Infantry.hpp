#pragma once

#include "Troop.hpp"

/* Troop represents an infantry soldier that runs around the terrain */
class Infantry : public Troop {
public:
    Infantry();
    Infantry(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d, const unsigned hp, const float v, const float radius);
    virtual void act(float dt);
private:
    virtual void fire();
    // Current target position
    sf::Vector2f targetPos_;
    // Pick the next target position within <wanderRadius>
    void pickTarget();
    // Idle timer between movements
    float idle_;
    float velocity_;
    float wanderRadius_;
};
