#include "MovingEntity.hpp"

/* Troop represents any moving unit that has hitpoints and can fire */
class Troop : public MovingEntity {
public:
    Troop();
    Troop(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d, const unsigned hp);
    virtual void act(float dt) = 0;
private:
    virtual void fire() = 0;
    unsigned hp_;
};
