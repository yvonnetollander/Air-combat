#pragma once

#include "Troop.hpp"
#include "Projectile.hpp"
#include "Explosion.hpp"

/* Plane is a class that represents a troop. 
   Plane takes parameters position, velocity, spritepath, rotation , status (dead or alive), health points and drag */
class Plane : public Troop {
public:
    virtual ~Plane();
    Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag, unsigned ammo_left, int team);

    virtual Projectile* Act(float dt, const sf::Vector2f& player_pos, const sf::Vector2f& player_velocity);
    void ToggleThrust();
    void Flip();
    Explosion* Explode();

protected:
    bool thrust_;
    bool inverted_;
    bool machine_gun_fired_ = false;
    float machine_gun_cooldown_ = 0.2f;
    float machine_gun_cooldown_left_ = 0.f;
    float drag_;
    float time_for_new_estimation_ = 0.f;   // Only relevant for the enemy planes.
    float time_between_estimations_ = 0.1f;
    bool FireMachineGun(float dt);
    virtual Projectile* Fire();
    virtual void UpdateCooldowns(float dt);
    virtual void ShootMachineGun();
    virtual Projectile* FireMachineGun();
};

/* PlayerPlane is user controllable plane and takes same parameters as Plane */
class PlayerPlane : public Plane {
public:
    PlayerPlane(const sf::Vector2f& p, const float r, const bool d, const unsigned hp, float drag, int team);
    // Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
    virtual Projectile* Act(float dt, Keys keys_pressed);
private:
    Keys keys_;
};