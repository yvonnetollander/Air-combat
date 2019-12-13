#pragma once

#include <SFML/Graphics.hpp>

/** Class World represents the game area.
    Creates a visible ground for the battlefield.

    Constructor parameters:
        int width:          width of the battlefield
        int height:         height of the airspace 
        int ground_height:  height of the ground rectangle
**/

class World {
public:
    World();
    ~World();
    World(int width, int height, int ground_height_ = 1000);
    // Return const reference to the ground rectangle  
    const sf::RectangleShape& GetGround() const;
    // Return height of the ground
    int GetGroundHeight() const;
    // Return Height of the airspace
    int GetHeight() const;
    // Return Width of the game area
    int GetWidth() const;

private:
    int width_;
    int height_;
    int ground_height_;
    sf::RectangleShape ground_;
};
