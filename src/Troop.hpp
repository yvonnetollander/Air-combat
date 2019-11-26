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

    virtual void Act(float dt, std::vector<MovingEntity*> moving_entities, const sf::Vector2f& player_pos, 
        const sf::Vector2f& player_velocity) = 0;
    const std::vector<Projectile*>& GetProjectiles();

protected:
    unsigned hp_;
    std::vector<Projectile*> projectiles_;
};
