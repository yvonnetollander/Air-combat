#include "MovingEntity.hpp"

/* Troop represents an infantry soldier that runs around the terrain */
class Troop : public MovingEntity {
public:
    Troop();
    Troop(const sf::Vector3f& p, const sf::Texture& t, const float r, const bool d, const float v, const float radius);
    void act(float dt);
private:
    // Current target position
    sf::Vector3f targetPos_;
    // Pick the next target position within <wanderRadius>
    void pickTarget();
    // Idle timer between movements
    float idle_;
    float velocity_;
    float wanderRadius_;
};
