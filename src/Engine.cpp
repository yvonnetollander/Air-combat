#include <iostream>
#include "Engine.hpp"
#include "util.hpp"
#include "globals.hpp"
#include "Background.hpp"
#include "Projectile.hpp"

Engine::Engine() : state_(GameState::menu) {
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
    ground_.setOrigin(0,-10);

    // TODO: An actual game configuration
    Player p1 = { "Sakari", sf::Color(255, 10, 10) };
    config_ = { true, p1, p1 };
    menu_.Create(&config_, window_.getSize());

    AddPlayerPlane(new PlayerPlane(sf::Vector2f(200.f, -200.f), 0.0f, false, 100, 0.65f));

    hud_.Create(sf::Vector2f(window_.getSize().x, window_.getSize().y));
    hud_.InitializeValues(player_->GetHP(), enemy_count_, player_->GetAmmoLeft(), "Machine Gun");

    // TODO: Fix the enemy plane image so that it doesn't need scaling.
    Plane* plane = new Plane(sf::Vector2f(1000.f, 0.0f), sf::Vector2f(100.f, 100.f), ROOTDIR + "/res/enemy_plane_orange.png", 0.0f, false, 100, 0.0f, 100);
    plane->SetScale(sf::Vector2f(0.15f, 0.15f));
    AddEnemy(plane);
    
    // TODO: Add several infantry soldiers with correct image
    Infantry *infantry = new Infantry(sf::Vector2f(0.f, 0.0f), ROOTDIR + "/res/plane007.png" , 0.0f, false, 10, 10, 100);
    AddEnemy(infantry);

    // Center camera and set to match window
    CenterCamera();
    ResizeCamera(window_.getSize().x, window_.getSize().y);

    // Align background
    backgrounds_.Current().FitToScreen(window_.getSize(), 2.f, 0.f);
}

Engine::~Engine() {
    for (auto entity : moving_entities_)
        delete entity;
    for (auto entity : static_entities_)
        delete entity;
    for (auto entity : enemies_)
        delete entity;
    delete player_;
}

void Engine::Start() {
    sf::Clock clock;

    while (window_.isOpen()) {
        // Restart the clock and save the elapsed time.
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        // Handle input
        sf::Event event;
        Input(event);

        // Update state & draw
        switch(state_)
        {
            case GameState::ingame:
                UpdateGame(dt);
                DrawGame();
                break;
            case GameState::menu:
                UpdateMenu(dt);
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

void Engine::AddEnemy(Troop* entity) {
    enemies_.push_back(entity);
    enemy_count_++;
}

void Engine::AddStatic(GameEntity* entity) {
    static_entities_.push_back(entity);
}

void Engine::AddPlayerPlane(PlayerPlane* entity) {
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
                    case GameState::ingame:
                        ResizeCamera(event.size.width, event.size.height);
                        backgrounds_.Current().Resize(event.size.width, event.size.height);
                        hud_.Resize(event.size.width, event.size.height);
                        break;
                    case GameState::menu:
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
            case sf::Event::MouseMoved:
                mouse_velocity_ = sf::Mouse::getPosition(window_) - mouse_pos_;
                mouse_pos_ = sf::Mouse::getPosition(window_);
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Button::Left) 
                    mouse_clicked_this_frame_= true;
                break;
            default:
                break;
        }
    }
}

void Engine::UpdateGame(float dt) {
    // Refresh camera view
    camera_.setCenter(player_->getPos());
    window_.setView(camera_);

    // Update background state 
    backgrounds_.Current().Update(player_->getVelocity(), dt);
    backgrounds_.Current().Recenter(camera_.getCenter());

    // Update moving entity states
    player_->Act(dt, moving_entities_, keys_pressed_);
    for (auto entity : moving_entities_)
        entity->Act(dt);
    for (auto troop : enemies_) {
        troop->Act(dt, moving_entities_, player_->getPos(), player_->getVelocity());
        for(auto bullet : troop->GetProjectiles())
            bullet->Act(dt, moving_entities_);
    }
    for(auto bullet : player_->GetProjectiles())
        bullet->Act(dt, moving_entities_);

    // Update HUD
    hud_.UpdateValues(player_->GetHP(), enemy_count_, player_->GetAmmoLeft());

    CheckProjectileHits();
}

void Engine::DrawGame() {
    window_.clear(backgrounds_.Current().GetBlendColor());
    // Background
    window_.draw(backgrounds_.Current().GetTexture(), backgrounds_.Current().GetTransform());
    // Terrain
    window_.draw(ground_);
    // Entities
    for(auto& entity : static_entities_)
        window_.draw(entity->getSprite(), entity->getTransform());
    for(auto& entity : moving_entities_)
        window_.draw(entity->getSprite(), entity->getTransform());
    for(auto& troop : enemies_) {
        window_.draw(troop->getSprite(), troop->getTransform());
        for(auto& bullet : troop->GetProjectiles()) {
            window_.draw(bullet->getSprite(), bullet->getTransform());
        }
    }
    for(auto& bullet : player_->GetProjectiles())
        window_.draw(bullet->getSprite(), bullet->getTransform());
    // HUD
    camera_.setCenter(window_.getSize().x / 2, window_.getSize().y / 2 + 2000);
    window_.setView(camera_);
    window_.draw(hud_.GetSprite(), hud_.GetTransform());

    window_.display();
}

void Engine::UpdateMenu(float dt) {
    // Update Background
    backgrounds_.Current().Recenter(camera_.getCenter());
    backgrounds_.Current().Update( 50.f * sf::Vector2f(mouse_velocity_.x, mouse_velocity_.y), dt);

    // Update menu, reset mouse click status
    menu_.Update(mouse_pos_, mouse_clicked_this_frame_);
    mouse_clicked_this_frame_ = false;

    // Switch to play state/exit when appropriate
    switch(menu_.GetState()) {
        case MenuState::play:
            state_ = GameState::ingame;
            break;
        case MenuState::quit:
            window_.close();
            break;
        default:
            break;
    }
}

void Engine::DrawMenu() {
    window_.clear(backgrounds_.Current().GetBlendColor());
    // Background
    sf::Transform bg_transform = backgrounds_.Current().GetTransform();
    window_.draw(backgrounds_.Current().GetTexture(), bg_transform.translate(0, window_.getSize().y / 2 + 1));
    // Menu
    window_.draw(menu_.GetSprite());
    window_.display();
}

void Engine::ResizeCamera(const float w, const float h) {
    camera_.setSize(w, h);
    window_.setView(camera_);
}

void Engine::CenterCamera() {
    camera_.setCenter(0, 0);
}

void Engine::CheckProjectileHits() {
    // Bad design, has to be changed :(
    std::vector<Projectile*> projectiles;
    for (auto p : player_->GetProjectiles()) {
        projectiles.push_back(p);
    }
    for (auto enemy: enemies_) {
        for (auto p : enemy->GetProjectiles()) {
            projectiles.push_back(p);
        }
    }

    for (auto p : projectiles) {
        for (auto enemy : enemies_) {
            if (p->WasTroopHit(enemy->getPos())) {
                enemy->ReduceHP(p->GetDamage());
            }
        }

        if (p->WasTroopHit(player_->getPos())) {
            player_->ReduceHP(p->GetDamage());
        }
    }

}