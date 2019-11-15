#include "util.hpp"
#include "Plane.hpp"

Plane::Plane()
    : Troop(), thrust_(false), inverted_(false), drag_(0.0f) {}

Plane::Plane(const sf::Vector2f& p, sf::Vector2f v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag)
    : Troop(p,v,spritepath,r,d,hp), thrust_(false), inverted_(false), drag_(drag) {}


void Plane::act(float dt, std::vector<MovingEntity*> moving_entities) {
    // These will need some mechanic to not just spasm out on button hold
    Move(dt);
} 

PlayerPlane::PlayerPlane(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag) 
    : Plane(p, sf::Vector2f(50.0f, 1.0f),spritepath, r, d, hp, drag) { }


 void PlayerPlane::press_keys(Keys keys_pressed) {
    if (keys_pressed.down)
        thrust_ = !thrust_;
    if (keys_pressed.up)
        inverted_ = !inverted_;

    bool corrected_left, corrected_right;
    
    if(inverted_) {
        corrected_left = keys_pressed.right;
        corrected_right = keys_pressed.left;
    }
    else {
        corrected_left = keys_pressed.left;
        corrected_right = keys_pressed.right;
    }

    velocity_ -= normalize(velocity_) * drag_;
    if(thrust_) {
        velocity_ += normalize(velocity_) * 1.0f;
    }
    
    if (corrected_left ^ corrected_right) {
        if (corrected_left) {
            
        }
    }
 }


