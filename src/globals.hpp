#pragma once

#include <string>
#include <unistd.h>
#include <SFML/Graphics.hpp>

// Define global variable for project root directory
extern std::string ROOTDIR;
// Set rootdir
void SetRootDir();

// Any fonts used in the game
namespace AirCombatFonts {
    extern sf::Font roboto_regular;
    // Load fonts
    void LoadFonts();
}
