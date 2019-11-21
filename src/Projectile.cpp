#include "Projectile.hpp"

Projectile::Projectile()
    : MovingEntity(), damage_radius_(10), damage_(10) {
        SetScale(sf::Vector2f(0.02f, 0.02f));
    }

Projectile::Projectile(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned damage_radius, 
    const unsigned damage)  :
    MovingEntity(p, v, spritepath, r, d), damage_radius_(damage_radius), damage_(damage) {
        SetScale(sf::Vector2f(0.02f, 0.02f));
    }

void Projectile::act(float dt, std::vector<MovingEntity*> moving_entities) {
    setPos(getPos() + (velocity_ * dt));
}