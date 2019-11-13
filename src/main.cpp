#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "globals.hpp"

#include "Engine.hpp"
#include "Background.hpp"

std::string ROOTDIR;

int main()
{
    // Set global variable for project root directory
    char cwd[1024];
    ROOTDIR = getcwd(cwd, sizeof(cwd)) ? std::string(cwd) : std::string("");
    ROOTDIR = ROOTDIR.substr(0, ROOTDIR.find("lib") - 1);

    Engine engine;
    engine.Start();
    return 0;
}
