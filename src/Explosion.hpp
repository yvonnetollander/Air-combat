#pragma once

#include "SFML/Graphics.hpp"
#include "MovingEntity.hpp"
#include "Projectile.hpp"

class Explosion : public MovingEntity {
public:
    Explosion();
    Explosion(sf::Vector2f position, sf::Vector2f scale = sf::Vector2f(1.f, 1.f));
    ~Explosion();
    virtual Projectile* Act(float dt);
private:
    int phase_;
    float timer_;
};