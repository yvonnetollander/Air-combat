#include <cmath>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

float len(const sf::Vector2f& vec) {
    return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}

sf::Vector2f normalize(const sf::Vector2f& vec) {
    return vec / len(vec);
}

sf::Vector2f rotate(const sf::Vector2f& vec, float rad) {
    float sn = std::sin(rad);
    float cs = std::cos(rad);
    return sf::Vector2f(vec.x * cs - vec.y * sn, vec.y * cs + vec.x * sn);
}

float randFloat() {
    return ((float) rand()) / (float) RAND_MAX;
}

sf::Vector2f lengthen(const sf::Vector2f& vec, float len) {
    return vec + len * normalize(vec);
}

sf::Vector2f lengthen(const sf::Vector2f& vec, float length, float max) {
    return std::min(len(vec) + length, max) * normalize(vec);
}
