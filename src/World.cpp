#include "World.hpp"

World::World()
    : width_(0), height_(0), ground_() { }

World::~World() { }

World::World(unsigned int width, unsigned int height) 
    : width_(width), height_(height) {
    ground_.setSize(sf::Vector2f(width_, height_));
    ground_.setFillColor(sf::Color(255, 204, 102));
    ground_.setOutlineColor(sf::Color(204, 102, 0));
    ground_.setOutlineThickness(10);
    ground_.setOrigin(0,-10);
}

const sf::RectangleShape& World::GetGround() const {
    return ground_;
}

