#pragma once

#include <SFML/Graphics.hpp>
#include "MovingEntity.hpp"
#include "Troop.hpp"

class Projectile : public MovingEntity {
public:
    Projectile(const sf::Vector2f& position, const sf::Vector2f& direction, const int damage, Troop* shooter);
    ~Projectile();
    void Act(float dt, Engine& engine);
private:
    int damage_;
    Troop* shooter_;
    sf::Vector2f velocity_;
};
