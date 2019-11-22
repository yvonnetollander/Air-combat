#pragma once

#include <SFML/Graphics.hpp>
#include "CombatEntity.hpp"
#include "Troop.hpp"

class Projectile : public CombatEntity {
public:
    Projectile(const sf::Vector2f& position, const sf::Vector2f& direction, const int damage, Troop* shooter);
    ~Projectile();
  //  std::vector<CombatEntity*>& Act(float dt, const std::vector<CombatEntity*>& combat_entities);
private:
    int damage_;
    Troop* shooter_;
    sf::Vector2f velocity_;
};
