#include "Troop.hpp"

Troop::Troop() {}

Troop::Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp) : 
    MovingEntity(p, v, spritepath, r, d), hp_(hp) {}

Troop::~Troop() {
    for (auto& p : projectiles_) {
        delete p;
    }
}

const std::vector<Projectile*>& Troop::GetProjectiles() {
    return projectiles_;
}
