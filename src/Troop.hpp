#pragma once

#include "util.hpp"
#include "MovingEntity.hpp"
#include "Projectile.hpp"
#include <vector>

/* Troop represents any moving unit that has hitpoints and can fire */

class Troop : public MovingEntity {
public:
    Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp);
    Troop();
    virtual ~Troop();

    virtual void act(float dt, std::vector<MovingEntity*> moving_entities) = 0;
    const std::vector<Projectile*>& GetProjectiles();

protected:
    unsigned hp_;
    std::vector<Projectile*> projectiles_;
};
