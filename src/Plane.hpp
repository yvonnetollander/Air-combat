#pragma once

#include "Troop.hpp"
#include "Projectile.hpp"
#include "Explosion.hpp"

/* Plane is a class that represents a troop. 
   Plane takes parameters position, velocity, spritepath, rotation , status (dead or alive), health points and drag */
class Plane : public Troop {
public:
    virtual ~Plane();
    Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag, unsigned ammo_left, int team, int max_x, int min_y);

    virtual Projectile* Act(float dt, const sf::Vector2f& player_pos, const sf::Vector2f& player_velocity);
    void ToggleThrust();
    void Flip();
    Explosion* Explode();

    // Check if the plane is able to land on the ground or  being killed as hitting to the ground
    void Landing(int x_ground);
protected:
    bool thrust_;
    bool inverted_;
    bool machine_gun_fired_ = false;
    float machine_gun_cooldown_ = 0.2f;
    float machine_gun_cooldown_left_ = 0.f;
    float drag_;
    float time_for_new_estimation_ = 0.f;   // Only relevant for the enemy planes.
    float time_between_estimations_ = 1.5f;
    sf::Vector2f destination_;
    bool is_chasing_player_ = true;
    float time_for_changing_behaviour = 5.0f;
    int max_x_;
    int min_y_;

    bool FireMachineGun(float dt);
    virtual Projectile* Fire();
    virtual void UpdateCooldowns(float dt);
    virtual void ShootMachineGun();
    virtual Projectile* FireMachineGun();
};

/* PlayerPlane is user controllable plane and takes same parameters as Plane */
class PlayerPlane : public Plane {
public:
    PlayerPlane(const sf::Vector2f& p, const float r, const bool d, const unsigned hp, float drag, int team, int max_x, int min_y);
    // Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
    virtual Projectile* Act(float dt, Keys keys_pressed);
private:
    Keys keys_;
};