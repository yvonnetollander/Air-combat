#include "World.hpp"

World::World()
    : width_(0), height_(0), ground_() { }

World::~World() { }

unsigned int World::GetGroundY() const {
    return ground_y_;
}

World::World(unsigned int width, unsigned int height, unsigned int ground_y) 
    : width_(width), height_(height + ground_y), ground_y_(ground_y) {
    ground_.setSize(sf::Vector2f(width_, ground_y));
    ground_.setFillColor(sf::Color(255, 204, 102));
    ground_.setOutlineColor(sf::Color(204, 102, 0));
    ground_.setOutlineThickness(10);
    ground_.setOrigin(0,-10);
}

const sf::RectangleShape& World::GetGround() const {
    return ground_;
}

