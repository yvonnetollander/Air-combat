#include "Troop.hpp"

Troop::Troop() {}

Troop::Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp, unsigned ammo_left, int team) : 
    MovingEntity(p, v, spritepath, r, d, team), hp_(hp), ammo_left_(ammo_left) { }

unsigned Troop::GetAmmoLeft() {
    return ammo_left_;
}

unsigned Troop::GetHP() {
    return hp_;
}

void Troop::ReduceHP(unsigned amount) {
    if (amount >= hp_) {
        kill();
        hp_ = 0;
    }
    else {
        hp_ -= amount;
    }
}