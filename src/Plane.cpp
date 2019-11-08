#include <Plane.hpp>
#include <util.cpp>

Plane::Plane()
    : Troop(), thrust_(false), drag_(0.0f), inverted_(false), velocity_() {}

Plane::Plane(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d, const unsigned hp, float drag)
    : Troop(p,t,r,d,hp), thrust_(false), drag_(drag), inverted_(false), velocity_() {}

void Plane::act(float dt, bool left, bool right, bool down, bool up) {
    // These will need some mechanic to not just spasm out on button hold
    if (down)
        thrust_ = !thrust_;
    if (up)
        inverted_ = !inverted_;

    bool corrected_left, corrected_right;
    
    if(inverted_) {
        corrected_left = right;
        corrected_right = left;
    }
    else {
        corrected_left = left;
        corrected_right = right;
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