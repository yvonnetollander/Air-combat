#pragma once

#include "MovingEntity.hpp"
#include "Projectile.hpp"

// Class for animated explosions

class Explosion : public MovingEntity {
public:
    Explosion();
    Explosion(sf::Vector2f position, float scale = 1.f);
    ~Explosion();
    virtual Projectile* Act(float dt);
private:
    int phase_;
    float timer_;
};