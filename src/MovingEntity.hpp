#include "GameEntity.hpp"

class MovingEntity : public GameEntity {
public:
    MovingEntity();
    MovingEntity(const sf::Vector3f& p, const sf::Texture& t, const float r, const bool d);
    virtual void act() = 0;
};
