#pragma once

#include "Troop.hpp"
#include "Projectile.hpp"
#include <vector>

/* Plane is a class that represents a troop. 
   Plane takes parameters position, velocity, spritepath, rotation , status (dead or alive), health points and drag */
class Plane : public Troop {
public:
    Plane();
    Plane(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag);
    virtual ~Plane() {}

    virtual void act(float dt, std::vector<MovingEntity*> moving_entities);
    void ToggleThrust();
    void Flip();
protected:
    bool thrust_;
    bool inverted_;
    float drag_;
};

/* PlayerPlane is user controllable plane and takes same parameters as Plane */
class PlayerPlane : public Plane {
public:
    PlayerPlane(const sf::Vector2f& p, const float r, const bool d, const unsigned hp, float drag);
    // Create custom behaviour for the player's plane by overriding the default logic in the Plane class's act method.
    virtual void act(float dt, std::vector<MovingEntity*> moving_entities, Keys keys_pressed);
private:
    void fire();
    Keys keys_;
};