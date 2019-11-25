#pragma once

#include <SFML/Graphics.hpp>
#include "MovingEntity.hpp"

/* This class represents a projectile that troops can fire. */

class Projectile : public MovingEntity {
public:

    /* Parameters for the constructor:
       p: position
       v: velocity
       spritepath: illustration of the object
       r: rotation
       d: is this GameEntity dead
       damage_radius: how far from the target's position does this projectile cause damage
       damage: how much does the target lose hitpoints when this projectile hits the target
    */
    Projectile();
    Projectile(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned damage_radius, 
        const unsigned damage);
    ~Projectile();
    
    virtual void Act(float dt, std::vector<MovingEntity*> moving_entities);

private:
    const unsigned damage_radius_;
    const unsigned damage_;
};
