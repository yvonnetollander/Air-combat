#include "Runway.hpp"

/* ****** Runway ****** */
Runway::Runway(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, const bool team)
    : GameEntity(p, spritepath, r, d), team_(team), hp_(hp) {}
