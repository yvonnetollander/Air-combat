#pragma once

#include "Troop.hpp"
#include "Projectile.hpp"

/* Plane is a class that represents a troop. 
   Plane takes parameters position, velocity, spritepath, rotation , status (dead or alive), health points and drag */
class Plane : public Troop {
public:
    virtual ~Plane();
    Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag);
    virtual Projectile* FireMachineGun();
    virtual bool FireMachineGun(float dt);
    virtual std::vector<CombatEntity*>* Act(float dt, const std::vector<CombatEntity*>& combat_entities);
protected:
    bool thrust_;
    bool inverted_;
    bool machine_gun_fired_ = false;
    float machine_gun_cooldown_ = 0.05;
    float machine_gun_cooldown_left_ = 0.f;
    float drag_;
};

/* PlayerPlane is user controllable plane and takes same parameters as Plane */
class PlayerPlane : public Plane {
public:
    PlayerPlane(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag); 
    // Method to listen the key presses which control the plane
    void press_keys(Keys keys_pressed);
    // Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.

private:
    void fire() {}
};