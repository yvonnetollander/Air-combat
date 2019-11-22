#include "Troop.hpp"

Troop::Troop(const sf::Vector2f& p, const sf::Vector2f& v, const std::string spritepath, const float r, const bool d, const unsigned hp) : 
    CombatEntity(p, v, spritepath, r, d), hp_(hp) {}

Troop::~Troop() { }

