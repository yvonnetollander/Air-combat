#pragma once

#include <vector>
#include "GameEntity.hpp"

/* MovingEntity is an abstract class that represents a game objects (GameEntity)
   that can also move according to some internal logic.
   All moving game objects inherit this class. 
   MovingEntity takes parameters position, illustration of the object, rotation and status (dead or alive) */
class MovingEntity : public GameEntity {
public:
    MovingEntity();
    virtual ~MovingEntity() {}
    MovingEntity(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d);
    virtual void act(float dt, std::vector<MovingEntity*> moving_entities) = 0;
};

