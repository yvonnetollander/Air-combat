#include "util.hpp"
#include "Plane.hpp"
#include "globals.hpp"
#include <iostream>

#define PI 3.14159265358979f

/* ****** Plane ****** */

Plane::~Plane() { }

Plane::Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag)
    : Troop(p,v,spritepath,r,d,hp), thrust_(false), inverted_(false), drag_(drag) {}

void Plane::act(float dt, std::vector<MovingEntity*> moving_entities) {
    Move(dt);
}

void Plane::ShootMachineGun() {
    machine_gun_fired_ = true;
}

void Plane::FireMachineGun() {
    if (machine_gun_fired_ && machine_gun_cooldown_left_ <= 0.f) {
        float damage_radius = 10;
        sf::Vector2f bullet_velocity = lengthen(velocity_, 1000);
        sf::Vector2f bullet_pos = pos_ + (normalize(velocity_) * 100.0f);
        projectiles_.push_back(new Projectile(bullet_pos, bullet_velocity, ROOTDIR + "/res/bullet_small.png", 0.f, false, damage_radius, 10));
        machine_gun_fired_ = false;
        machine_gun_cooldown_left_ = machine_gun_cooldown_;
    }
}

void Plane::Fire() {
    FireMachineGun();
}

void Plane::UpdateCooldowns(float dt) {
    machine_gun_cooldown_left_ -= dt;
}


/* ****** PlayerPlane ****** */

// Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
// Todo: Include fire and collision

void Plane::ToggleThrust() {
    thrust_ = !thrust_;
}

void Plane::Flip() {
    inverted_ = !inverted_;
    SetScale(sf::Vector2f(1.f, inverted_ ? -1.f : 1.f));
}

/* ****** PlayerPlane ****** */
PlayerPlane::PlayerPlane(const sf::Vector2f& p, const float r, const bool d, const unsigned hp, float drag) 
    : Plane(p, sf::Vector2f(20, 0), ROOTDIR + "/res/biplane.png", r, d, hp, drag) {}

// Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
void PlayerPlane::act(float dt, std::vector<MovingEntity*> moving_entities, Keys keys_pressed) {
    const float turning_mult = 40.f;
    const float thrush_mult = 120.f;
    const float pi = 3.141592653;

    UpdateCooldowns(dt);

    // Flip plane on up key
    if (keys_pressed.up && !keys_.up) Flip();

    float rotation_speed_in_degrees = 1;
    float rotation_speed_in_radians = rotation_speed_in_degrees * 3.14159265 / 180;
    // Toggle thrust on down key
    if (keys_pressed.down && !keys_.down) ToggleThrust();

    // Movement
    if (keys_pressed.right) {
        Rotate(dt * turning_mult);
        velocity_ = rotate(velocity_, dt * turning_mult * pi / 180.f);
    }
    if (keys_pressed.left) {
        Rotate(-dt * turning_mult);
        velocity_ = rotate(velocity_, -dt * turning_mult * pi / 180.f);
    }

    if (keys_pressed.d) {
        ShootMachineGun();
    }

    // Apply thrust & drag
    if (thrust_) {
        velocity_ = lengthen(velocity_, dt * thrush_mult);
    }
    if(len(velocity_) > 0.0001f) // Prevent direction loss on a zero vector
        velocity_ *= 1.f - (drag_ * dt);

    Fire();
    Move(dt);

    // Update previous key status
    keys_ = keys_pressed;
}
