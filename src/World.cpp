#include "World.hpp"

World::World()
    : width_(0), height_(0), ground_() { }

World::~World() { }

World::World(int width, int height, int ground_height) 
    : width_(width), height_(height), ground_height_(ground_height) {
    ground_.setSize(sf::Vector2f(width_, ground_height));
    ground_.setFillColor(sf::Color(255, 204, 102));
    ground_.setOutlineColor(sf::Color(204, 102, 0));
    ground_.setOutlineThickness(10);
    ground_.setOrigin(0,-10);
}

int World::GetGroundHeight() const {
    return ground_height_;
}

int World::GetHeight() const {
    return height_;
}

int World::GetWidth() const {
    return width_;
}

const sf::RectangleShape& World::GetGround() const {
    return ground_;
}

