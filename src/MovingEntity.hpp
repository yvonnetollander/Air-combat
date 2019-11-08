#include "GameEntity.hpp"

/* MovingEntity is an abstract class tat  represents a game objects (GameEntity)
   that can also move according to some internal logic.
   All moving game objects inherit this class. */
class MovingEntity : public GameEntity {
public:
    MovingEntity();
    MovingEntity(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d);
    virtual void act(float dt) = 0;
};

