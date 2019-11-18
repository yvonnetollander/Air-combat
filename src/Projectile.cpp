#include "Projectile.hpp"
#include "globals.hpp"
#include <utils.h>

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& direction, const int damage, Troop* shooter)
    : damage_(damage), shooter_(shooterr) {
        std::string spritepath = ROOTDIR + "bullet.png";
        float rotation = 0.0;
        bool dead = false;
        // Calculate unit vector for direction
        sf::Vector2f unit_direction = normalize(direction);
        sf::Vector2f velocity = direction * 100;
        MovingEntity(position, velocity, spritepath, rotation, dead);
    }

Projectile::~Projectile() {
    ~MovingEntity();
}

void Act(float dt, Engine& engine) {
    Move(dt);
    // CheckCollision(moving_entities)
}
// Todo: collision check with template functions