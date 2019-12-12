#include <stdlib.h>
#include <algorithm>
#include "Infantry.hpp"
#include "util.hpp"
#include "globals.hpp"

/* ****** Infantry ****** */
Infantry::Infantry()
    : Troop(), targetPos_(), idle_(0), wanderRadius_(0) { PickTarget(); }

Infantry::Infantry(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, const float radius, const int min_x, const int max_x, unsigned ammo_left, int team)
    : Troop(p, sf::Vector2f(50.0f, 0.0f), spritepath, r, d, hp, ammo_left, team), targetPos_(), idle_(0), wanderRadius_(radius), min_x_(min_x), max_x_(max_x) { PickTarget(); }

Projectile* Infantry::Act(float dt, const sf::Vector2f& player_pos, const sf::Vector2f& player_velocity) {
    if (!dead_) {
        sf::Vector2f diff = targetPos_ - getPos();
        float movement = velocity_.x * dt;
        UpdateCooldown(dt);
        // If Infantry is idle, decrease the remaining time and fire
        if(idle_ > 0) {
            idle_ = std::max(0.0f, idle_ - dt);
            if (ammo_left_ > 0)
                return Fire(player_pos);
        }
        // If infantry is not idle change its position
        else {
            // If the Infantry can reach the target position, it moves to the target position and it is set to be idle for random time
            if(len(diff) < movement) {
                setPos(targetPos_);
                idle_ = randFloat() * 5.0f;
                PickTarget();
            }
            // Otherwise, the infantry moves closer to target position
            else {         
                setPos(getPos() + normalize(diff) * movement);
            }
        }
    }

    return nullptr;
} 

void Infantry::PickTarget() {
    float random = randFloat();
    // Infantry move on the x-axis only
    int new_x = 20.0f * (random - 0.5f) * wanderRadius_;
    if (new_x < min_x_) { new_x = min_x_; }
    else if (new_x > max_x_) { new_x = max_x_; }
    if ( (new_x < pos_.x && x_multiplier_ == 1) || (new_x > pos_.x && x_multiplier_ == -1) ) FlipX();
    targetPos_ = sf::Vector2f(new_x, 0);
}

Projectile* Infantry::FireMachineGun(const sf::Vector2f& player_pos) {
    if (machine_gun_cooldown_left_ <= 0.f) {
        float damage_radius = 10.f;
        // Set the bullet go towards the player
        sf::Vector2f bullet_velocity = lengthen(player_pos, 1000);
        sf::Vector2f bullet_pos = pos_ + (normalize(velocity_) * 10.0f);
        Projectile* projectiles = new Projectile(bullet_pos, bullet_velocity, ROOTDIR + "/res/bullet_small.png", 0.f, false, damage_radius, 10, team_);
        machine_gun_cooldown_left_ = machine_gun_cooldown_;
        ammo_left_ -= 1;
        return projectiles;
    }
    return nullptr;
}

void Infantry::UpdateCooldown(float dt) {
    machine_gun_cooldown_left_ -= dt;
}

Projectile* Infantry::Fire(const sf::Vector2f& player_pos) {
    return FireMachineGun(player_pos);
}
