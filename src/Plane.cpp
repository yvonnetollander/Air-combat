#include "util.hpp"
#include "Plane.hpp"
#include <iostream>

/* ****** Plane ****** */
Plane::Plane()
    : Troop(), thrust_(false), inverted_(false), drag_(0.0f) {}

Plane::Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag)
    : Troop(p,v,spritepath,r,d,hp), thrust_(false), inverted_(false), drag_(drag) {}


void Plane::act(float dt, std::vector<MovingEntity*> moving_entities) {
    // These will need some mechanic to not just spasm out on button hold
    Move(dt);
} 

/* ****** PlayerPlane ****** */
PlayerPlane::PlayerPlane(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag) 
    : Plane(p, sf::Vector2f(50.0f, 20.0f), spritepath, r, d, hp, drag) {}

// Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
void PlayerPlane::act(float dt, std::vector<MovingEntity*> moving_entities) {
    float old_x = pos_.x;
    float old_y = pos_.y;
    float new_x = old_x + (velocity_.x * dt);   // v = ds / dt
    float new_y = old_y + (velocity_.y * dt);
    pos_ = sf::Vector2f(new_x, new_y);
}

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

    float rotation_speed_in_degrees = 0.2;
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
 }


