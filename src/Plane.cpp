#include "util.hpp"
#include "Plane.hpp"
#include "globals.hpp"
#include <iostream>
#include <stdlib.h>

#define PI 3.14159265358979f

/* ****** Plane ****** */
Plane::~Plane() { }

Plane::Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag, unsigned ammo_left, int team, int max_x, int min_y)
    : Troop(p, v, spritepath, r, d, hp, ammo_left, team), thrust_(false), inverted_(false), drag_(drag), destination_(0.f, 0.f), max_x_(max_x), min_y_(min_y) {}

Projectile* Plane::Act(float dt, const sf::Vector2f& player_pos, const sf::Vector2f& player_velocity) {
    if (!dead_) {
        UpdateCooldowns(dt);

        sf::Vector2f diff = player_pos - pos_;
        // Cosine of the angle between the <diff> and <velocity_> vectors.
        float cosine = dotProduct(diff, velocity_) / (len(diff) * len(velocity_));
        // If the angle is small enough, try to shoot the player.
        if (cosine > 0.9 && ammo_left_ > 0) {
            ShootMachineGun();
        }

        time_for_changing_behaviour -= dt;
        if (time_for_changing_behaviour <= 0.f) {
            time_for_changing_behaviour = 5.0f;
            is_chasing_player_ = !is_chasing_player_;
        }

        if (is_chasing_player_) {
            if (time_for_new_estimation_ <= 0.f) {
                time_for_new_estimation_ = time_between_estimations_;

                // Estimate where the player is after time <time_between_estimations_>.
                destination_ = player_pos + player_velocity * time_between_estimations_;
            }
            else {
                time_for_new_estimation_ -= dt;
                sf::Vector2f diff(destination_ - pos_);

                float diff_angle = getVectorAngle(diff) - getVectorAngle(velocity_);
                float turning_mult = 70.f;
                if (diff_angle > 0) {
                    // Rotate velocity to point in the direction of <destination_>.
                    Rotate(dt * turning_mult);
                    velocity_ = rotate(velocity_, dt * turning_mult * PI / 180.f);
                }
                else {
                    Rotate(-dt * turning_mult);
                    velocity_ = rotate(velocity_, -dt * turning_mult * PI / 180.f);
                }
            }
        }
        else {   // If not chasing the player ...
            // If the behaviour was just changed during the current method call, get a new destination_.
            if (time_for_changing_behaviour == 5.0f) {
                // x in [0, world_.GetWidth()], y in [-world_.GetHeight(), -0.2 * world_.GetHeight()]
                destination_ = sf::Vector2f(randFloat() * max_x_, abs(randFloat() * 0.8 * min_y_) + min_y_);
            }
            else {
                sf::Vector2f diff(destination_ - pos_);
                float diff_angle = getVectorAngle(diff) - getVectorAngle(velocity_);
                float turning_mult = 70.f;
                if (diff_angle > 0) {
                    // Rotate velocity to point in the direction of <destination_>.
                    Rotate(dt * turning_mult);
                    velocity_ = rotate(velocity_, dt * turning_mult * PI / 180.f);
                }
                else {
                    Rotate(-dt * turning_mult);
                    velocity_ = rotate(velocity_, -dt * turning_mult * PI / 180.f);
                }
            }
        }

        Projectile* projectiles = Fire();
        Move(dt);
        return projectiles;
    }
    return nullptr;
}

void Plane::Landing(int x_ground) {
    // Check if the plane hits the ground
    if (getPos().y > x_ground) {
        // If the plane is on the ground and taking off 
        // In other words the plane is going going upwards = the angle is between 180 and 360 degrees 
        // Do nothing
        if(getVectorAngle(getVelocity()) < 360 && getVectorAngle(getVelocity()) > 180) {

        }
        // If the plane is moving to the right, right side up
        // and hits the ground in smaller than 55 degree angle 
        // Set the plane move along the ground
        else if(!inverted_ && getVectorAngle(getVelocity()) >= 0 && getVectorAngle(getVelocity()) < 55) {
            velocity_ = sf::Vector2f(velocity_.x, 0.0f);
            rotation_ = 0;
        }
        // If the plane is moving to the left, right side up
        // and hits the ground in smaller than 55 degree angle
        // Set the plane move along the ground
        else if(inverted_ && getVectorAngle(getVelocity()) <= 180 && getVectorAngle(getVelocity()) > 125) {
            velocity_ = sf::Vector2f(velocity_.x, 0.0f);
            rotation_ = -180;
        }
        // Otherwise kill the player because it hits the ground
        else {
            kill();
        }
        
    }
}

void Plane::ShootMachineGun() {
    machine_gun_fired_ = true;
}

Projectile* Plane::FireMachineGun() {
    if (machine_gun_fired_ && machine_gun_cooldown_left_ <= 0.f) {
        float damage_radius = 100.f;
        sf::Vector2f bullet_velocity = lengthen(velocity_, 1000);
        sf::Vector2f bullet_pos = pos_ + (normalize(velocity_) * 100.0f);
        Projectile* p = new Projectile(bullet_pos, bullet_velocity, ROOTDIR + "/res/bullet_small.png", 0.f, false, damage_radius, 10, team_);
        machine_gun_fired_ = false;
        machine_gun_cooldown_left_ = machine_gun_cooldown_;
        ammo_left_ -= 1;
        return p;
    }
    else {
        return nullptr;
    }
}

Projectile* Plane::Fire() {
    return FireMachineGun();
}

void Plane::UpdateCooldowns(float dt) {
    machine_gun_cooldown_left_ -= dt;
}

void Plane::ToggleThrust() {
    thrust_ = !thrust_;
}

void Plane::Flip() {
    inverted_ = !inverted_;
    SetScale(sf::Vector2f(1.f, inverted_ ? -1.f : 1.f));
}

/* ****** PlayerPlane ****** */
PlayerPlane::PlayerPlane(const sf::Vector2f& p, const float r, const bool d, const unsigned hp, float drag, int team, int max_x, int min_y) 
    : Plane(p, sf::Vector2f(20, 0), ROOTDIR + "/res/biplane.png", r, d, hp, drag, 100, team, max_x, min_y) {}

// Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
Projectile* PlayerPlane::Act(float dt, Keys keys_pressed) {
    if (!dead_) {
        const float turning_mult = 70.f;
        const float thrush_mult = 120.f;

        UpdateCooldowns(dt);

        // Flip plane on up key
        if (keys_pressed.up && !keys_.up)
            Flip();

        // Toggle thrust on down key
        if (keys_pressed.down && !keys_.down)
            ToggleThrust();

        // Movement
        if (keys_pressed.right) {
            Rotate(dt * turning_mult);
            velocity_ = rotate(velocity_, dt * turning_mult * PI / 180.f);
        }
        if (keys_pressed.left) {
            Rotate(-dt * turning_mult);
            velocity_ = rotate(velocity_, -dt * turning_mult * PI / 180.f);
        }

        if (keys_pressed.d) {
            if (ammo_left_ > 0) {
                ShootMachineGun();
            }
        }

        // Apply thrust & drag
        if (thrust_)
            velocity_ = lengthen(velocity_, dt * thrush_mult);
        if(len(velocity_) > 0.0001f) // Prevent direction loss on a zero vector
            velocity_ *= 1.f - (drag_ * dt);

        Projectile* projectiles = Fire();
        Move(dt);

        // Update previous key status
        keys_ = keys_pressed;
        return projectiles;
    }
    return nullptr;
}