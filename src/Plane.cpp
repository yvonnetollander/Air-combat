#include "util.hpp"
#include "Plane.hpp"
#include "globals.hpp"
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

    // Flip plane on up key
    if (keys_pressed.up && !keys_.up) Flip();

    // Toggle thrust on down key
    if (keys_pressed.down && !keys_.down) ToggleThrust();

    // Movement
    if (keys_pressed.right) {
        Rotate(dt * turning_mult);
        velocity_ = rotate(velocity_, dt * turning_mult * M_PI / 180.f);
    }
    if (keys_pressed.left) {
        Rotate(-dt * turning_mult);
        velocity_ = rotate(velocity_, -dt * turning_mult * M_PI / 180.f);
    }

    // Apply thrust & drag
    if (thrust_) {
        velocity_ = lengthen(velocity_, dt * thrush_mult);
    }
    velocity_ *= 1.f - (drag_ * dt);

    Move(dt);

    // Update previous key status
    keys_ = keys_pressed;
}

