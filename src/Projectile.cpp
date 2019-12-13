#include "Projectile.hpp"

#include "globals.hpp"
#include "util.hpp"

Projectile::~Projectile() { }

Projectile::Projectile()
    : MovingEntity(), damage_radius_(10), damage_(10) {
        SetScale(sf::Vector2f(0.02f, 0.02f));
    }

Projectile::Projectile(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned damage_radius, 
    const unsigned damage, int team)
    : MovingEntity(p, v, spritepath, r, d, team), damage_radius_(damage_radius), damage_(damage), lifetime_(10.f) {}

Projectile* Projectile::Act(float dt) {
    lifetime_ -= dt;
    if (lifetime_ < 0.f) {
        kill();
    } else {
        setPos(getPos() + (velocity_ * dt));
    }
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