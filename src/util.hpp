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

// Increase length of given vector by len
sf::Vector2f lengthen(const sf::Vector2f& vec, float len);

// Increase length of given vector by len, capping at <max>
sf::Vector2f lengthen(const sf::Vector2f& vec, float len, float max);

sf::RectangleShape CreateCenteredRect(sf::FloatRect bounds, sf::Color color);
sf::Text CreateCenteredText(sf::String string, sf::FloatRect bounds, unsigned size, sf::Color color);
sf::Text CreateCenteredText(sf::String string, sf::Vector2f pos, unsigned size, sf::Color color);

// Center text to a ppint
void CenterText(sf::Text& t, sf::Vector2f center);

// Vector2u to Vector2f
sf::Vector2f ToFloatVec(const sf::Vector2u& v);

// Lighten a color
sf::Color Lighter(const sf::Color& c);
