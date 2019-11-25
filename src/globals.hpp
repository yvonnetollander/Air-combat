#pragma once

#include <string>
#include <unistd.h>
#include <SFML/Graphics.hpp>

// Enumeration for game and menu views/statuses
enum GameState { menu, ingame };
enum MenuState { index, options, credits, play, quit };

// Global variable for project root directory
extern std::string ROOTDIR;
void SetRootDir();

// Any fonts used in the game
namespace AirCombatFonts {
    extern sf::Font roboto_regular;
    // Load all fonts
    void LoadFonts();
}
