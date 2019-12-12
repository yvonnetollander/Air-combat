#include <cmath>
#include <stdlib.h>
#include <iostream>

#include "util.hpp"
#include "globals.hpp"
#include <SFML/Graphics.hpp>

#define PI 3.14159265358979f

float len(const sf::Vector2f& vec) {
    return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}

float getVectorAngle(const sf::Vector2f& v) {
    float atan_angle = atan2(v.y, v.x);
    float angle = atan_angle * 180 / PI;   // (-180, 180)
    if (angle < 0) {
        angle += 360;   // (0, 360)
    }
    return angle;
}

float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
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

sf::RectangleShape CreateCenteredRect(sf::FloatRect bounds, sf::Color color) {
    sf::RectangleShape r(sf::Vector2f(bounds.width, bounds.height));
    r.setOrigin(bounds.width/2.f, bounds.height/2.f);
    r.setFillColor(color);
    r.setPosition(bounds.left, bounds.top);
    return r;
}

sf::Text CreateCenteredText(sf::String string, sf::FloatRect bounds, unsigned size, sf::Color color) {
    sf::Text t(string, AirCombatFonts::roboto_regular, size);
    const sf::FloatRect local_bounds = t.getLocalBounds();
    t.setOrigin(local_bounds.width/2.f, local_bounds.height/2.f);
    t.setPosition(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    t.setFillColor(color);
    return t;
}

sf::Text CreateCenteredText(sf::String string, sf::Vector2f pos, unsigned size, sf::Color color) {
    return CreateCenteredText(string, sf::FloatRect(pos.x, pos.y, 0.f, 0.f), size, color);
}

void CenterText(sf::Text& t, sf::Vector2f center) {
    const sf::FloatRect local_bounds = t.getLocalBounds();
    t.setOrigin(local_bounds.width/2.f, local_bounds.height/2.f);
    t.setPosition(center);
}

sf::Text CreatePositionedText(sf::String string, float x, float y, unsigned size, sf::Color color) {
    sf::Text t(string, AirCombatFonts::roboto_regular, size);
    t.setPosition(x, y);
    t.setFillColor(color);
    return t;
}

sf::Vector2f ToFloatVec(const sf::Vector2u& v) {
    return sf::Vector2f(float(v.x), float(v.y));
}

sf::Color Lighter(const sf::Color& c) {
    constexpr float factor = 0.2f;
    const float dr = (255 - c.r) * factor;
    const float dg = (255 - c.g) * factor;
    const float db = (255 - c.b) * factor;
    return sf::Color(c.r + dr, c.g  + dg, c.b + db);
}

void CapCameraToWorld(sf::View& camera, World w) {
    sf::Vector2f c = camera.getCenter();
    sf::Vector2f s = camera.getSize();
    // Deltas for camera view and world borders
    float dl = std::min(c.x - (s.x/2.f), 0.f);
    float dr = std::max(c.x + (s.x/2.f) - w.GetWidth(), 0.f);
    float dt = std::min(c.y - (s.y/2.f) + w.GetHeight(), 0.f);
    float db = std::max(c.y + (s.y/2.f) - 0.1f * w.GetHeight(), 0.f);
    // Move accordingly
    camera.move(-dl-dr, -dt-db);
}

