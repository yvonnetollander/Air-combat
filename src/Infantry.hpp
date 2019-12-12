#pragma once

#include "Troop.hpp"
#include "Projectile.hpp"

/* Troop represents an infantry soldier that runs around the terrain */
class Infantry : public Troop {
public:
    Infantry();
    Infantry(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, const float radius, const int min_x, const int max_x, unsigned ammo_left, int team = 2);
    virtual ~Infantry() {}
    virtual Projectile* Act(float dt, const sf::Vector2f& player_pos, const sf::Vector2f& player_velocity);
private:
    // Current target position
    sf::Vector2f targetPos_;
    // Pick the next target position within <wanderRadius>
    void PickTarget();
    // Idle timer between movements
    float idle_;
    float wanderRadius_;
    int min_x_;
    int max_x_;
    // Handle shooting
    float machine_gun_cooldown_ = 0.2f;
    float machine_gun_cooldown_left_ = 0.f;
    virtual void UpdateCooldown(float dt);
    virtual Projectile* FireMachineGun(const sf::Vector2f& player_pos);
    virtual Projectile* Fire(const sf::Vector2f& player_pos);
};
