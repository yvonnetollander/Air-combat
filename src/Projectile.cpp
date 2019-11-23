#include "Projectile.hpp"
#include "globals.hpp"
#include "util.hpp"
/*
Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& direction, const int damage, Troop* shooter) {
        std::string spritepath = ROOTDIR + "/res/bullet.png";
        float rotation = 0.0;
        bool dead = false;
        // Calculate unit vector for direction
        sf::Vector2f unit_direction = normalize(direction);
        sf::Vector2f velocity = unit_direction;
        CombatEntity(position, velocity, spritepath, rotation, dead);
        // MUUTA!
*/
Projectile::~Projectile() { }

// Todo: collision check with template functions


Projectile::Projectile()
    : MovingEntity(), damage_radius_(10), damage_(10) {
        SetScale(sf::Vector2f(0.02f, 0.02f));
    }

// sf::vector2f CalculateProjectileVelocity

Projectile::Projectile(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned damage_radius, 
    const unsigned damage)  :
    MovingEntity(p, v, spritepath, r, d), damage_radius_(damage_radius), damage_(damage) {
        SetScale(sf::Vector2f(0.02f, 0.02f));
    }

void Projectile::act(float dt, std::vector<MovingEntity*> moving_entities) {
    setPos(getPos() + (velocity_ * dt));
}
