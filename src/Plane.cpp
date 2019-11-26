#include "util.hpp"
#include "Plane.hpp"
#include "globals.hpp"
#include <iostream>

#define PI 3.14159265358979f

/* ****** Plane ****** */
Plane::~Plane() { }

Plane::Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag, unsigned ammo_left)
    : Troop(p, v, spritepath, r, d, hp, ammo_left), thrust_(false), inverted_(false), drag_(drag) {}

void Plane::Act(float dt, std::vector<MovingEntity*> moving_entities, const sf::Vector2f& player_pos, 
        const sf::Vector2f& player_velocity) {
    if (!dead_) {
        if (time_for_new_estimation_ <= 0.f) {
            time_for_new_estimation_ = time_between_estimations_;

            // Estimate where the player is after time <time_between_estimations_>. Change velocity to point to that direction.
            sf::Vector2f player_new_pos = player_pos + player_velocity * time_between_estimations_;

            sf::Vector2f pos_diff = player_new_pos - pos_;
            sf::Vector2f new_velocity = len(velocity_) * normalize(pos_diff);
            velocity_ = new_velocity;
            rotation_ = getVectorAngle(new_velocity);
        }
        else {
            time_for_new_estimation_ -= dt;
        }

        Move(dt);
    }
}

void Plane::ShootMachineGun() {
    machine_gun_fired_ = true;
}

void Plane::FireMachineGun() {
    if (machine_gun_fired_ && machine_gun_cooldown_left_ <= 0.f) {
        float damage_radius = 100.f;
        sf::Vector2f bullet_velocity = lengthen(velocity_, 1000);
        sf::Vector2f bullet_pos = pos_ + (normalize(velocity_) * 100.0f);
        projectiles_.push_back(new Projectile(bullet_pos, bullet_velocity, ROOTDIR + "/res/bullet_small.png", 0.f, false, damage_radius, 50));
        machine_gun_fired_ = false;
        machine_gun_cooldown_left_ = machine_gun_cooldown_;
        ammo_left_ -= 1;
    }
}

void Plane::Fire() {
    FireMachineGun();
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
PlayerPlane::PlayerPlane(const sf::Vector2f& p, const float r, const bool d, const unsigned hp, float drag) 
    : Plane(p, sf::Vector2f(20, 0), ROOTDIR + "/res/biplane.png", r, d, hp, drag, 100) {}

// Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
void PlayerPlane::Act(float dt, std::vector<MovingEntity*> moving_entities, Keys keys_pressed) {
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

    Fire();
    Move(dt);

    // Update previous key status
    keys_ = keys_pressed;
}