#include "Projectile.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <iostream>

Projectile::~Projectile() { }

// Todo: collision check with template functions

Projectile::Projectile()
    : MovingEntity(), damage_radius_(10), damage_(10) {
        SetScale(sf::Vector2f(0.02f, 0.02f));
    }

Projectile::Projectile(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned damage_radius, 
    const unsigned damage, int team)
    : MovingEntity(p, v, spritepath, r, d, team), damage_radius_(damage_radius), damage_(damage) {}

Projectile* Projectile::Act(float dt) {
    setPos(getPos() + (velocity_ * dt));
    return nullptr;
}

bool Projectile::WasTroopHit(sf::Vector2f troop_pos) {
    sf::Vector2f diff = troop_pos - pos_;
    float dist = len(diff);
    return dist <= damage_radius_;
}

unsigned Projectile::GetDamage() {
    return damage_;
}