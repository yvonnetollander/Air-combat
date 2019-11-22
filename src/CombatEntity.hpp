#pragma once

#include "MovingEntity.hpp"

class CombatEntity : public MovingEntity {
public:
    CombatEntity();
    CombatEntity(const sf::Vector2f& position, const sf::Vector2f& velocity, const std::string spritepath, const float rotation, const bool dead);
    virtual ~CombatEntity();
    virtual std::vector<CombatEntity*>* Act(float dt, const std::vector<CombatEntity*>& combat_entities);
};