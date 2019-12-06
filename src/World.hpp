#pragma once

#include <SFML/Graphics.hpp>

class World {
public:
    World();
    ~World();
    World(unsigned int width, unsigned int height, unsigned int ground_y = 1000);
    const sf::RectangleShape& GetGround() const;
    unsigned int GetGroundY() const;

private:
    unsigned int width_;
    unsigned int height_;
    unsigned int ground_y_;
    sf::RectangleShape ground_;
};
