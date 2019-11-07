#include "Engine.hpp"
#include <iostream>

Engine::Engine() {
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();   // Fullscreen mode.
    window_.create(desktop, "Air Combat Game");

    if (!background_texture_.loadFromFile("../../../res/background.png")) {
        std::cout << background_texture_.getMaximumSize() << std::endl;
    }
    sf::Vector2u TextureSize = background_texture_.getSize(); //Get size of texture.
    sf::Vector2u WindowSize = window_.getSize();             //Get size of window.

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

    background_sprite_.setTexture(background_texture_);
    background_sprite_.setScale(ScaleX, ScaleY);
}

void Engine::Start() {
    sf::Clock clock;

    while (window_.isOpen()) {
        // Restart the clock and save the elapsed time.
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        sf::Event event;

        Input(event);
        Update(dt);
        Draw();
    }
}

void Engine::Input(sf::Event& event) {
    while (window_.pollEvent(event)) {
        // Check the type of the event.
        switch (event.type) {
            // window closed
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Key::Escape:
                        window_.close();
                        break;
                    case sf::Keyboard::Key::Left:
                        std::cout << "Left" << std::endl;
                        break;
                    default:
                    break;
                }
            // We don't process other types of events.
            default:
                break;
        }
    }
}

void Engine::Update(float dt) {
    // Update locations...
}

void Engine::Draw() {
    // Clear the last frame.
    window_.clear(sf::Color::White);
    // Draw the background.
    window_.draw(background_sprite_);
    // Show background on the screen.
    window_.display();
}