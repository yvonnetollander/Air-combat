#include "MovingEntity.hpp"

MovingEntity::MovingEntity() :
    GameEntity() {}

MovingEntity::MovingEntity(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d) : 
    GameEntity(p, spritepath, r, d) {}
