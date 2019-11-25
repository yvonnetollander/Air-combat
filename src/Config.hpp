#pragma once

#include <SFML/Graphics.hpp>

// Simple data structures for player and game information

struct Player {
    std::string name;
    sf::Color color;
};

struct Config {
    bool sounds;
    Player player_1;
    Player player_2;
};
