#pragma once

#include "CombatEntity.hpp"
#include "util.hpp"

/* Troop represents any moving unit that has hitpoints and can fire */

class Troop : public CombatEntity {
public:

    Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp);
    virtual ~Troop();
protected:
    unsigned hp_;
};
