#include "MovingEntity.hpp"

/* Troop represents an infantry soldier that runs around the terrain */
class Troop : public MovingEntity {
public:
    Troop();
    Troop(const sf::Vector3f& p, const sf::Texture& t, const float r, const bool d, const unsigned hp);
    void act(float dt) = 0;
private:
    void fire();
    unsigned hp_;
};
