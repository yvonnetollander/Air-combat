#pragma once

#include "Troop.hpp"

class Plane : public Troop {
public:
    Plane();
    Plane(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag);
    virtual void act(float dt) {}
    void act(float dt, std::vector<MovingEntity*> moving_entities);
protected:
    bool thrust_;
    bool inverted_;
    float drag_;
    sf::Vector2f velocity_;
};

class PlayerPlane : public Plane {
public:
    PlayerPlane(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, float drag)
        : Plane(p, spritepath, r, d, hp, drag) { }
    void press_keys(Keys keys_pressed);

    void move(float dt) {}
private:
    void fire() {} 
};