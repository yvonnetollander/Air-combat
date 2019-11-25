#include <iostream>
#include "globals.hpp"

void SetRootDir() {
    char cwd[1024];
    ROOTDIR = getcwd(cwd, sizeof(cwd)) ? std::string(cwd) : std::string("");
    ROOTDIR = ROOTDIR.substr(0, ROOTDIR.find("lib") - 1);
}


namespace AirCombatFonts {
    void LoadFonts() {
        if(!AirCombatFonts::roboto_regular.loadFromFile(ROOTDIR + "/res/Roboto-Regular.ttf"))
            std::cerr << "Error loading font roboto_regular: " << ROOTDIR << "/res/Roboto-Regular.ttf";
    }
}

