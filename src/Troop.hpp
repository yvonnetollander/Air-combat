#pragma once

#include "MovingEntity.hpp"
#include "util.hpp"
#include "Projectile.hpp"
#include <vector>

/* Troop represents any moving unit that has hitpoints and can fire */

class Troop : public MovingEntity {
public:
    Troop();
    Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp);
    virtual ~Troop();

    virtual void act(float dt, std::vector<MovingEntity*> moving_entities) = 0;
    const std::vector<Projectile*>& GetProjectiles();

private:
    virtual void fire() = 0;
    unsigned hp_;

protected:
    std::vector<Projectile*> projectiles_;
};

class PlayerTroop : virtual public Troop {
public:
    virtual void press_keys(Keys keys_pressed);
};
