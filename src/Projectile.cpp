#include "Projectile.hpp"
#include "globals.hpp"
#include "util.hpp"

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& direction, const int damage, Troop* shooter) {
        std::string spritepath = ROOTDIR + "/res/bullet.png";
        float rotation = 0.0;
        bool dead = false;
        // Calculate unit vector for direction
        sf::Vector2f unit_direction = normalize(direction);
        sf::Vector2f velocity = unit_direction;
        CombatEntity(position, velocity, spritepath, rotation, dead);
        // MUUTA!
        damage_ = damage;
        shooter_ = shooter;
    }

Projectile::~Projectile() { }

// Todo: collision check with template functions