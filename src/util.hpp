#pragma once

#include <cmath>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

// Returns the length of a given vector
float len(const sf::Vector2f& vec);

// Return a normalized version of a given vector
sf::Vector2f normalize(const sf::Vector2f& vec);

sf::Vector2f rotate(const sf::Vector2f& vec, float rad);

// Returns a random floating point number between 0 and 1
float randFloat();
