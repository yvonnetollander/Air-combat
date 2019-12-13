#include "Explosion.hpp"
#include "SFML/Graphics.hpp"
#include "globals.hpp"

Explosion::Explosion()
    : MovingEntity(), phase_(0), timer_(0.f) {}

Explosion::Explosion(sf::Vector2f position, float scale) 
    : MovingEntity(position, sf::Vector2f(0.f, 0.f), ROOTDIR + "/res/explosion.png", 0, false), phase_(0), timer_(0.1) {
        // Scale the explosion
        SetScale(sf::Vector2f(scale, scale));
        // Cut rectangle texture and reposition it in the middle of the original one
        sf::IntRect rect = sf::IntRect(0, 0, 96, 96);
        sf::Vector2f pos = getPos();
        setPos(pos.x + scale * (getSize().x / 2 - getSize().y / 2), pos.y);
        setTextureRect(rect);
    }

Explosion::~Explosion() {}

Projectile* Explosion::Act(float dt) {
    timer_ -= dt;
    if (timer_ < 0) {
        // Change the texture
        if (phase_ < 12) {
            phase_ += 1;
            timer_ += 0.1;
            sf::IntRect rect = sf::IntRect(phase_ * 96, 0, 96, 96);
            setTextureRect(rect);
        } else {
        // Set the status to dead
            kill();
        }
    }
    return nullptr;
}
