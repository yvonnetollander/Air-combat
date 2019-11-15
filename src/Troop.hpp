#pragma once

#include "MovingEntity.hpp"
#include "util.hpp"

/* Troop represents any moving unit that has hitpoints and can fire */

class Troop : public MovingEntity {
public:
    Troop();

    Troop(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp);
    virtual void act(float dt, std::vector<MovingEntity*> moving_entities) = 0;
    
    virtual void move(float dt) = 0;

private:
    virtual void fire() = 0;
    unsigned hp_;
};

class PlayerTroop : virtual public Troop {
public:
    virtual void press_keys(Keys keys_pressed);
};
