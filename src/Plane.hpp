#pragma once

#include "Troop.hpp"

/* Plane is a class that represents a troop. 
   Plane takes parameters position, velocity, spritepath, rotation , status (dead or alive), health points and drag */
class Plane : public Troop {
public:
    Plane();
    Plane(const sf::Vector2f& p, const sf::Vector2f v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag);
    virtual void act(float dt) {}
    void act(float dt, std::vector<MovingEntity*> moving_entities);
protected:
    bool thrust_;
    bool inverted_;
    float drag_;
};

/* PlayerPlane is user controllable plane and takes same parameters as Plane */
class PlayerPlane : public Plane {
public:
    PlayerPlane(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag); 
    // Method to listen the key presses which control the plane
    void press_keys(Keys keys_pressed);
private:
    void fire() {} 
};