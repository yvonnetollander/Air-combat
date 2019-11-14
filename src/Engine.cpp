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

    // Load background
    if (!background_texture_.loadFromFile(ROOTDIR + "/res/background.png"))
        std::cerr << "Failed to load background" << std::endl;
    background_sprite_.setTexture(background_texture_);

    // Set camera to initial view (for now the entire background)
    camera_ = sf::View(sf::FloatRect(0.f, 0.f, background_texture_.getSize().x, background_texture_.getSize().y));
    ResetView();
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

    AddPlayer(new PlayerPlane(sf::Vector2f(200.f, 200.f), ROOTDIR + "/res/plane007.png", 0.0f, false, 100, 0.0f));

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
                ResetView();
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
    player_->press_keys(keys_pressed_);
    // Update background state 
    bg_.update(sf::Vector2f(1,1), dt);
    // Update moving entity states
    for (auto entity : moving_entities_)
        entity->act(dt, moving_entities_);
}

void Engine::Draw() {
    // Clear window
    window_.clear(sf::Color::Black);

    // Draw background.
    window_.draw(background_sprite_);
    window_.draw(bg_.getTexture(), bg_.getTransform());

    // Draw static entities
    for(auto& entity : static_entities_)
        window_.draw(entity->getSprite(), sf::RenderStates(entity->getTransform()));

    // Draw moving entities
    for(auto& entity : moving_entities_)
        window_.draw(entity->getSprite(), sf::RenderStates(entity->getTransform()));

    // Refresh window
    window_.display();
}

void Engine::ResetView() {
    sf::Vector2u window_size = window_.getSize();
    float window_aspect_ratio = (float) window_size.x / (float) window_size.y;

    // Figure out relative scaling for letterboxing
    float w = 1.f , h = 1.f;
    if(target_aspect_ratio_ < window_aspect_ratio)
        w = ((float) window_size.y * target_aspect_ratio_) / window_size.x;
    else if(target_aspect_ratio_ > window_aspect_ratio)
        h = ((float) window_size.x / target_aspect_ratio_) / window_size.y;

    // Reset camera viewport to new letterbox on window
    camera_.setViewport(sf::FloatRect((1.f - w)/2, (1.f - h)/2, w, h));
    window_.setView(camera_);
}
