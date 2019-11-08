#include "MovingEntity.hpp"

MovingEntity::MovingEntity() :
    GameEntity() {}

MovingEntity::MovingEntity(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d) : 
    GameEntity(p, t, r, d) {}
