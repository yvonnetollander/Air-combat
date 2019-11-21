#include <iostream>
#include "Engine.hpp"
#include "util.hpp"
#include "globals.hpp"
#include "Background.hpp"

Engine::Engine() : bg_(duskMountainBackground()) {
    // Initialize window to 0.7 x screen height at target aspect ratio
    auto video = sf::VideoMode().getDesktopMode();
    video.height *= 0.7f;
    video.width = video.height * target_aspect_ratio_;
    window_.create(video, "Air Combat Game");

    // Set up a simpele ground terrain
    ground_.setSize(sf::Vector2f(1500, 170));
    ground_.setFillColor(sf::Color(255, 204, 102));
    ground_.setOutlineColor(sf::Color(204, 102, 0));
    ground_.setOutlineThickness(10);
    ground_.setOrigin(0,0);

    AddPlayer(new PlayerPlane(sf::Vector2f(200.f, -200.f), 0.0f, false, 100, 0.65f));

    // Camera starting position
    sf::Vector2f center = sf::Vector2f(0, 0);

    // Set camera to match window
    resetView(window_.getSize().x, window_.getSize().y);
    camera_.setCenter(center);

    // Align background
    bg_.fitToScreen(center, window_.getSize(), 1.5f, 10.f);
}

Engine::~Engine() {
    for (auto entity : moving_entities_)
        delete entity;
    for (auto entity : static_entities_)
        delete entity;
    delete player_;
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

void Engine::AddPlayer(PlayerPlane* entity) {
    player_ = entity;
    AddMoving(entity);
}

void Engine::Input(sf::Event& event) {
    while (window_.pollEvent(event)) {
        // Check the type of the event.
        switch (event.type) {
            // window closed
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::Resized:
                resetView(event.size.width, event.size.height);
                bg_.resize(event.size.width, event.size.height);
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Key::Escape:
                        window_.close();
                        break;
                    case sf::Keyboard::Key::Left:
                        keys_pressed_.left = true;
                        break;
                    case sf::Keyboard::Key::Right:
                        keys_pressed_.right = true;
                        break;
                    case sf::Keyboard::Key::Up:
                        keys_pressed_.up = true;
                        break;
                    case sf::Keyboard::Key::Down:
                        keys_pressed_.down = true;
                        break;
                    case sf::Keyboard::Key::D:
                        keys_pressed_.d = true;
                        std::cout << "pew pew" << std::endl;
                        break;
                    case sf::Keyboard::Key::P:
                        std::cout << "Left: " << keys_pressed_.left << "Right: " << keys_pressed_.right << "Up: " << keys_pressed_.up << "Down: " << keys_pressed_.down << std::endl;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Key::Left:
                        keys_pressed_.left = false;
                        break;
                    case sf::Keyboard::Key::Right:
                        keys_pressed_.right = false;
                        break;
                    case sf::Keyboard::Key::Up:
                        keys_pressed_.up = false;
                        break;
                    case sf::Keyboard::Key::Down:
                        keys_pressed_.down = false;
                        break;
                    case sf::Keyboard::Key::D:
                        keys_pressed_.d = false;
                        break;
                    default:
                        break;
                }
                break;
            // We don't process other types of events.
            default:
                break;
        }
    }
}

void Engine::Update(float dt) {
    camera_.setCenter(player_->getPos());

    player_->act(dt, moving_entities_, keys_pressed_);

    // Update background state 
    bg_.update(player_->getVelocity(), dt);
    bg_.recenter(camera_.getCenter());

    // Update moving entity states
    for (auto entity : moving_entities_)
        entity->act(dt, moving_entities_);

    for(auto& bullet : player_->GetProjectiles())
        bullet->act(dt, moving_entities_);

    // Simplified camera movements before plane is configured
    
    /*
    if(keys_pressed_.up) camera_.move(0,-1);
    if(keys_pressed_.down) camera_.move(0,1);
    if(keys_pressed_.left) camera_.move(-1,0);
    if(keys_pressed_.right) camera_.move(1,0);
    */

    // Refresh view after movement changes
    window_.setView(camera_);
}

void Engine::Draw() {
    // Clear window
    window_.clear(bg_.getBlendColor());

    // Draw background
    window_.draw(bg_.getTexture(), bg_.getTransform());

    // Draw ground
    window_.draw(ground_);

    // Draw static entities
    for(auto& entity : static_entities_)
        window_.draw(entity->getSprite(), sf::RenderStates(entity->getTransform()));

    // Draw moving entities
    for(auto& entity : moving_entities_)
        window_.draw(entity->getSprite(), sf::RenderStates(entity->getTransform()));

    for(auto& bullet : player_->GetProjectiles())
        window_.draw(bullet->getSprite(), sf::RenderStates(bullet->getTransform()));

    // Refresh window
    window_.display();
}

void Engine::resetView(const float w, const float h) {
    camera_.setSize(w, h);
    window_.setView(camera_);
}
