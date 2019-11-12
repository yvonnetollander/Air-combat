#include <iostream>
#include "Engine.hpp"

extern std::string ROOTDIR;

Engine::Engine() {
    // Init window to current desktop size
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    window_.create(desktop, "Air Combat Game");

    /* TODO: scale the original backgound picture to screen size and remove scaling below */
    if (!background_texture_.loadFromFile(ROOTDIR + "/res/background.png"))
        std::cout << background_texture_.getMaximumSize() << std::endl;
    
    sf::Vector2u tecture_size = background_texture_.getSize();
    sf::Vector2u window_size = window_.getSize();

    float scale_x = (float) window_size.x / tecture_size.x;
    float scale_y = (float) window_size.y / tecture_size.y;

    background_sprite_.setTexture(background_texture_);
    background_sprite_.setScale(scale_x, scale_y);
}

Engine::~Engine() {
    for (auto entity : moving_entities_)
        delete entity;
    for (auto entity : static_entities_)
        delete entity;
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

void Engine::AddMoving(MovingEntity* entity) {
    moving_entities_.push_back(entity);
}

void Engine::AddStatic(GameEntity* entity) {
    static_entities_.push_back(entity);
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
                    case sf::Keyboard::Key::Right:
                        std::cout << "Right" << std::endl;
                        break;
                    case sf::Keyboard::Key::Up:
                        std::cout << "Up" << std::endl;
                        break;
                    case sf::Keyboard::Key::Down:
                        std::cout << "Down" << std::endl;
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
    for (auto entity : moving_entities_)
        entity->act(dt);
}

void Engine::Draw() {
    // Clear the last frame.
    window_.clear(sf::Color::White);
    // Draw the background.
    window_.draw(background_sprite_);
    // Show background on the screen.
    window_.display();
}