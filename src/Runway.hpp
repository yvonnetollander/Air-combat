#pragma once

#include "GameEntity.hpp"

/*  Runway is a class that represents a static GameEntity. 
    The game starts from a runway and if the player is able to complete the mission it lands back to the runway in order to win the game.
    At the base the player can change the machine, the refuel the plane and refill the bombs. Player should also protect the base.
    Runway takes parameters position, spritepath, rotation, status (destroyed or alive), health points and team.
    Team boolean is true if the runway belongs to own team and false if its opponents runway. */
class Runway : public GameEntity {
public:
    Runway(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, const bool team);
    
private:
    unsigned hp_;
    bool team_;

};
