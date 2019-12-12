#pragma once

#include "util.hpp"
#include "MovingEntity.hpp"
#include "Projectile.hpp"

/*  Class Troop represents any moving unit that has health points and can use a weapon.
    Parameters for the constructor:
    p: position
    v: velocity
    spritepath: illustration of the object
    r: objects rotation in degrees as a float
    d: boolean of the objects status. True: object is alive, false: objects is dead or destroyed.
    hp: health points. If healt points decreases to zero the infantry is set dead.
    ammo_left: the amount of ammos the troop has
    team: team the troop belongs
*/
class Troop : public MovingEntity {
public:
    Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, unsigned ammo_left, int team);
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
