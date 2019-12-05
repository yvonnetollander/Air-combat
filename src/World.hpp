#pragma once

#include <SFML/Graphics.hpp>

class World {
public:
    World();
    ~World();
    World(unsigned int width, unsigned int height);
    const sf::RectangleShape& GetGround() const;

private:
    unsigned int width_;
    unsigned int height_;
    sf::RectangleShape ground_;
};
