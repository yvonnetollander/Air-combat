#include "Troop.hpp"

Troop::Troop() :
    MovingEntity(), hp_(100) {}

Troop::Troop(const sf::Vector3f& p, const sf::Texture& t, const float r, const bool d, const unsigned hp) : 
    MovingEntity(p, t, r, d), hp_(hp) {}

void Troop::fire() {}
