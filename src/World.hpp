#pragma once

#include <SFML/Graphics.hpp>

class World {
public:
    World();
    ~World();
    World(int width, int height, int ground_height_ = 1000);
    const sf::RectangleShape& GetGround() const;
    int GetGroundHeight() const;
    int GetHeight() const;
    int GetWidth() const;

private:
    int width_;
    int height_;
    int ground_height_;
    sf::RectangleShape ground_;
};
