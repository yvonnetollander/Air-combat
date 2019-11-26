#include "Troop.hpp"

Troop::Troop() {}

Troop::Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, unsigned ammo_left) : 
    MovingEntity(p, v, spritepath, r, d), hp_(hp), ammo_left_(ammo_left) { }

Troop::~Troop() {
    for (auto p : projectiles_) {
        delete p;
    }
}

unsigned Troop::GetAmmoLeft() {
    return ammo_left_;
}

unsigned Troop::GetHP() {
    return hp_;
}

void Troop::ReduceHP(unsigned amount) {
    if (amount >= hp_) {
        kill();
    }
    else {
        hp_ -= amount;
    }
}

const std::vector<Projectile*>& Troop::GetProjectiles() {
    return projectiles_;
}
