#include "util.hpp"
#include "Plane.hpp"
#include <iostream>

/* ****** Plane ****** */

Plane::~Plane() { }

Plane::Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag)
    : Troop(p,v,spritepath,r,d,hp), thrust_(false), inverted_(false), drag_(drag) {}


 std::vector<CombatEntity*>* Plane::Act(float dt, const std::vector<CombatEntity*>& combat_entities) {
    // These will need some mechanic to not just spasm out on button hold
    Move(dt);
    if (FireMachineGun(dt)) {
        Projectile* projectile = FireMachineGun();
        std::cout << "ASD" << std::endl;
        std::vector<CombatEntity*>* projectiles = new std::vector<CombatEntity*>;
        projectiles->push_back(projectile);
        std::cout << projectiles->size() << std::endl;
        return projectiles;
    }
    return nullptr;
} 

Projectile* Plane::FireMachineGun() {
    machine_gun_fired_ = false;
    return new Projectile(pos_, velocity_, 20, this);
}

bool Plane::FireMachineGun(float dt) {
    machine_gun_cooldown_left_ -= dt;
    if (machine_gun_fired_ && machine_gun_cooldown_left_ < 0) {
        machine_gun_cooldown_left_ = machine_gun_cooldown_;
        return true;
    }
    return false;
}



/* ****** PlayerPlane ****** */
PlayerPlane::PlayerPlane(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag) 
    : Plane(p, sf::Vector2f(50.0f, 20.0f), spritepath, r, d, hp, drag) {}

// Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
// Todo: Include fire and collision


void PlayerPlane::press_keys(Keys keys_pressed) {
    if (keys_pressed.up) {
        inverted_ = !inverted_;
    }

    bool corrected_left, corrected_right;

    if (inverted_) {
        corrected_left = keys_pressed.right;
        corrected_right = keys_pressed.left;
    }
    else {
        corrected_left = keys_pressed.left;
        corrected_right = keys_pressed.right;
    }

    float rotation_speed_in_degrees = 1;
    float rotation_speed_in_radians = rotation_speed_in_degrees * 3.14159265 / 180;

    if (corrected_left) {
        rotation_ -= rotation_speed_in_degrees;   // Update both the rotation float variable ...
        velocity_ = rotate(velocity_, -rotation_speed_in_radians);   // ... and the velocity vector.
    }

    if (corrected_right) {
        rotation_ += rotation_speed_in_degrees;
        velocity_ = rotate(velocity_, rotation_speed_in_radians);
    }
    
    // velocity_ -= normalize(velocity_) * drag_;   // Ignore drag for now.

    if (keys_pressed.down) {
        thrust_ = !thrust_;
    }

    if (thrust_) {
        velocity_ += normalize(velocity_) * 0.2f;
    }

    if (keys_pressed.d) {
        machine_gun_fired_ = true;
    }
}
