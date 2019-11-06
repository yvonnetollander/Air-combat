#include "Engine.hpp"
#include <iostream>

Engine::Engine() {
    
    /*
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
*/
    window_.create(sf::VideoMode(800, 600), "Test");

    if (!background_texture_.loadFromFile("../../../src/background.png")) {
        std::cout << background_texture_.getMaximumSize() << std::endl;
    }
    

    
    background_sprite_.setTexture(background_texture_);
    
}

void Engine::Start() {
    sf::Clock clock;   // For measuring time.
    while (window_.isOpen()) {
        // Restart the clock and save the elapsed time.
        //sf::Time time = clock.restart();
        //float dt = time.asSeconds();
        //Draw();
        sf::Event event;
        while (window_.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window_.close();
        }
        
        
        Draw();
    }
}

void Engine::Draw() {
    // Clear the last frame.
    window_.clear(sf::Color::White);

    // Draw the background.
    window_.draw(background_sprite_);

    // Show background on the screen.
    window_.display();
}