#pragma once

#include "util.hpp"
#include "MovingEntity.hpp"
#include "Projectile.hpp"
#include <vector>

/* Troop represents any moving unit that has hitpoints and can fire */

class Troop : public MovingEntity {
public:
    Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, unsigned ammo_left);
    Troop();
    virtual ~Troop() {}

    virtual Projectile* Act(float dt, const sf::Vector2f& player_pos, const sf::Vector2f& player_velocity) = 0;
    unsigned GetHP();
    void ReduceHP(unsigned amount);
    unsigned GetAmmoLeft();

protected:
    unsigned hp_;
    unsigned ammo_left_;
};
