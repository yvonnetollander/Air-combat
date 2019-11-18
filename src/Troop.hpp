#pragma once

#include "MovingEntity.hpp"
#include "util.hpp"

/* Troop represents any moving unit that has hitpoints and can fire */

class Troop : public MovingEntity {
public:
    Troop();

    Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp);

    virtual void act(float dt, Engine& engine) = 0;

protected:
    unsigned hp_;
};
