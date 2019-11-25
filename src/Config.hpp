#pragma once

#include <SFML/Graphics.hpp>

struct Player {
    std::string name;
    sf::Color color;
};

struct Config {
    bool sounds;
    Player player_1;
    Player player_2;
};
