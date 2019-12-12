#pragma once

#include "Troop.hpp"
#include "Projectile.hpp"

/*  Class infantry represents an infantry soldier that represents a troop.
    An infantry soldier takes a target position, runs to the position and is set to be idle for a random time.
    While the infantry soldier is idle, it tries to shoot the player.

    Parameters for the constructor:
    p: position
    spritepath: illustration of the object
    r: objects rotation in degrees as a float
    d: boolean of the objects status. True: object is alive, false: objects is dead or destroyed.
    hp: health points. If healt points decreases to zero the infantry is set dead.
    radius: radius within the infantry can wander
    min_x: minimum x-coordinate value infantry is allowed to go
    max_x: maximum x-coordinate value infantry is allowed to go
    ammo_left: the amount of ammos the infantry has
*/
class Infantry : public Troop {
public:
    Infantry();
    Infantry(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d, const unsigned hp, const float radius, const int min_x, const int max_x, unsigned ammo_left, int team = 2);
    virtual ~Infantry() {}
    // Infantry can act if it is not dead
    // If infantry is idle, it tries to shoot the player and decreases its remaining idle time
    // Infantry can shoot the player if it has ammos left and the weapon has cooled down after previous shooting
    // Otherwise it moves towards the target position
    // If it reaches the target position, it is set to be idle for random time and it is given a new target position
    virtual Projectile* Act(float dt, const sf::Vector2f& player_pos, const sf::Vector2f& player_velocity);
private:
    // Current target position
    sf::Vector2f targetPos_;
    // Pick the next target position within <wanderRadius>
    void PickTarget();
    // Idle timer between movements
    float idle_;
    // Length of the radius within infantry is allowed to wander
    float wanderRadius_;
    // minimum x-coordinate value where the infantry is allowed to wander
    int min_x_;
    // maximum x-coordinate value where the infantry is allowed to wander
    int max_x_;
    // Constant value how it takes for a machine gun to cool down
    float machine_gun_cooldown_ = 0.2f;
    // Timer value for cool down
    float machine_gun_cooldown_left_ = 0.f;
    // Decrease the remaining cool down time
    virtual void UpdateCooldown(float dt);
    // If machine gun is cool down it fires a bullet towards the player
    // It creates a new projectile which is get a direction and velosity based on the players position
    // The player position is given as a parameter
    // After firing the machine gun is set to cool down and the amount of ammos left is decreased by one 
    virtual Projectile* FireMachineGun(const sf::Vector2f& player_pos);
    // Method to use command different weapons to fire
    // Returns FireMachineGun method
    virtual Projectile* Fire(const sf::Vector2f& player_pos);
};
