#include <iostream>
#include "Engine.hpp"
#include "util.hpp"
#include "globals.hpp"
#include "Background.hpp"   

Engine::Engine() : state_(State::menu) {
    // Initialize window to 0.7 x screen height
    auto video = sf::VideoMode().getDesktopMode();
    video.height *= 0.7f;
    video.width = video.height * target_aspect_ratio_;
    window_.create(video, "Air Combat Game");

    // Set up a simple ground terrain
    // TODO: Move terrain generation to somewhere separate and improve
    ground_.setSize(sf::Vector2f(1500, 170));
    ground_.setFillColor(sf::Color(255, 204, 102));
    ground_.setOutlineColor(sf::Color(204, 102, 0));
    ground_.setOutlineThickness(10);
    ground_.setOrigin(0,0);

    Player p1 = { "Sakari", sf::Color(255, 10, 10) };
    config_ = { true, p1, p1 };
    menu_.Create(&config_, window_.getSize());

    AddPlayer(new PlayerPlane(sf::Vector2f(200.f, -200.f), 0.0f, false, 100, 0.65f));

    CenterCamera();
    // Set camera to match window
    ResizeCamera(window_.getSize().x, window_.getSize().y);

    // Align background
    backgrounds_.Current().fitToScreen(window_.getSize(), 2.f, 10.f);
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

        // Todo: use integer microseconds
        float dt = time.asSeconds();

        // Handle input
        sf::Event event;
        Input(event);

        // Update state & draw
        switch(state_)
        {
            case State::game:
                UpdateGame(dt);
                DrawGame();
                break;
            case State::menu:
                UpdateMenu();
                DrawMenu();
                break;
            default:
                break;
        }
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
                switch(state_)
                {
                    case State::game:
                        ResizeCamera(event.size.width, event.size.height);
                        backgrounds_.Current().resize(event.size.width, event.size.height);
                        break;
                    case State::menu:
                        ResizeCamera(event.size.width, event.size.height);
                        menu_.Resize(event.size.width, event.size.height);
                        break;
                    default:
                        break;
                }
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
                    case sf::Keyboard::Key::B:
                        backgrounds_.Switch();
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

void Engine::UpdateGame(float dt) {
    // Refresh camera view
    camera_.setCenter(player_->getPos());
    window_.setView(camera_);

    player_->act(dt, moving_entities_, keys_pressed_);

    // Update background state 
    backgrounds_.Current().update(player_->getVelocity(), dt);
    backgrounds_.Current().recenter(camera_.getCenter());

    // Update moving entity states
    for (auto entity : moving_entities_) {
        entity->act(dt);
    }

    for(auto& bullet : player_->GetProjectiles())
        bullet->act(dt, moving_entities_);

}

void Engine::DrawGame() {
    window_.clear(backgrounds_.Current().getBlendColor());
    // Draw background
    window_.draw(backgrounds_.Current().getTexture(), backgrounds_.Current().getTransform());
    // Draw ground
    window_.draw(ground_);
    // Draw entities
    for(auto& entity : static_entities_)
        window_.draw(entity->getSprite(), sf::RenderStates(entity->getTransform()));
    for(auto& entity : moving_entities_)
        window_.draw(entity->getSprite(), sf::RenderStates(entity->getTransform()));
    for(auto& bullet : player_->GetProjectiles())
        window_.draw(bullet->getSprite(), sf::RenderStates(bullet->getTransform()));
    window_.display();
}

void Engine::UpdateMenu() {
    const sf::Vector2i mouse = sf::Mouse::getPosition(window_);
    menu_.Update(mouse);
    if(keys_pressed_.up) camera_.move(0,-1);
    if(keys_pressed_.down) camera_.move(0,1);
    if(keys_pressed_.left) camera_.move(-1,0);
    if(keys_pressed_.right) camera_.move(1,0);
}

void Engine::DrawMenu() {
    window_.clear(sf::Color::White);

    // sf::RectangleShape r;
    // r.setSize(sf::Vector2f(100, 100));
    // r.setFillColor(sf::Color::Black);
    // r.setOrigin(0,0);
    // window_.draw(r);


    window_.draw(menu_.getSprite());

    // Refresh window
    window_.display();

}

void Engine::ResizeCamera(const float w, const float h) {
    camera_.setSize(w, h);
    window_.setView(camera_);
}

void Engine::CenterCamera() {
    camera_.setCenter(window_.getSize().x / 2, window_.getSize().y / 2);
}
