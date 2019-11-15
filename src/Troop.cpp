#include "Troop.hpp"

Troop::Troop() :
    MovingEntity(), hp_(100) {}

Troop::Troop(const sf::Vector2f& p, const sf::Vector2f v, const std::string spritepath, const float r, const bool d, const unsigned hp) : 
    MovingEntity(p, v, spritepath, r, d), hp_(hp) {}

void Troop::fire() {}
