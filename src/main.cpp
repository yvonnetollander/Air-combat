#include <SFML/Graphics.hpp>

#include "globals.hpp"
#include "Engine.hpp"

std::string ROOTDIR;
sf::Font AirCombatFonts::roboto_regular;

int main()
{
    SetRootDir();
    AirCombatFonts::LoadFonts();

    Engine engine;
    engine.Start();
    return 0;
}
