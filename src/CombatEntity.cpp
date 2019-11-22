#include "CombatEntity.hpp"

CombatEntity::CombatEntity()
    : MovingEntity() { }

CombatEntity::CombatEntity(const sf::Vector2f& position, const sf::Vector2f& velocity, const std::string spritepath, const float rotation, const bool dead)
    : MovingEntity(position, velocity, spritepath, rotation, dead) { }

CombatEntity::~CombatEntity() { }

std::vector<CombatEntity*>* CombatEntity::Act(float dt, const std::vector<CombatEntity*>& combat_entities) {
    return nullptr;
}