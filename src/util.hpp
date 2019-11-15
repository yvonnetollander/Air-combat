#pragma once

#include <cmath>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

struct Keys {
    bool up = false;    // flip
    bool down = false;  // stop engine
    bool left = false;  // rotate
    bool right = false; // rotate
    bool d = false;     // shoot
};

// Returns the length of a given vector
float len(const sf::Vector2f& vec);

// Return a normalized version of a given vector
sf::Vector2f normalize(const sf::Vector2f& vec);

sf::Vector2f rotate(const sf::Vector2f& vec, float rad);

// Returns a random floating point number between 0 and 1
float randFloat();
