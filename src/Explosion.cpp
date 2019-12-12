#include "Explosion.hpp"
#include "globals.hpp"

Explosion::Explosion()
    : MovingEntity(), phase_(0), timer_(0.f) {}

Explosion::Explosion(sf::Vector2f position, sf::Vector2f scale) 
    : MovingEntity(position, sf::Vector2f(0.f, 0.f), ROOTDIR + "/res/explosion.png", 0, false), phase_(0), timer_(0.15) {
        sf::IntRect rect = sf::IntRect(0, 0, 96, 96);
        sf::Vector2f pos = getPos();
        setPos(pos.x + getSize().x / 2, pos.y);
        setTextureRect(rect);
        SetScale(scale);
    }

Explosion::~Explosion() {}

Projectile* Explosion::Act(float dt) {
    timer_ -= dt;
    if (timer_ < 0) {
        if (phase_ < 12) {
            phase_ += 1;
            timer_ += 0.15;
            sf::IntRect rect = sf::IntRect(phase_ * 96, 0, 96, 96);
            setTextureRect(rect);
        } else {
            kill();
        }
    }
    return nullptr;
}
