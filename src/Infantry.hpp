#pragma once

#include "Troop.hpp"

/* Troop represents an infantry soldier that runs around the terrain */
class Infantry : public Troop {
public:
    Infantry();
    Infantry(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, const float radius);
    virtual ~Infantry() {}
    virtual void Act(float dt, std::vector<MovingEntity*> moving_entities, const sf::Vector2f& player_pos, 
        const sf::Vector2f& player_velocity);
private:
    virtual void fire();
    // Current target position
    sf::Vector2f targetPos_;
    // Pick the next target position within <wanderRadius>
    void pickTarget();
    // Idle timer between movements
    float idle_;
    float wanderRadius_;
};
