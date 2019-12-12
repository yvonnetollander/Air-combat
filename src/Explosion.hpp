#pragma once

#include "MovingEntity.hpp"
#include "Projectile.hpp"

/** Class Explosion represents explosions in the battlefield.
    Creates an animated explosion with scaleable size.

    Constructor parameters:
        sf::Vector2f position       position of the entity
        float scale                 size scaling for the explosion

    Explosions are relative to time, and are updated with Act(dt)
**/

class Explosion : public MovingEntity {
public:
    Explosion();
    Explosion(sf::Vector2f position, float scale = 1.f);
    ~Explosion();
    // Change explosion phase as time passes
    virtual Projectile* Act(float dt);
private:
    // Counter for explosion phase
    int phase_;
    // Timer for changing texture
    float timer_;
};