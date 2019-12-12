#include <iostream>
#include "Engine.hpp"
#include "util.hpp"
#include "globals.hpp"
#include "Background.hpp"
#include "Projectile.hpp"
#include "World.hpp"

Engine::Engine() : state_(GameState::menu), mouse_clicked_this_frame_(false) {
    // Initialize window to 0.7 x screen height
    auto video = sf::VideoMode().getDesktopMode();
    video.height *= 0.7f;
    video.width = video.height * target_aspect_ratio_;
    window_.create(video, "Air Combat Game");

    world_ = World(10000, 1000);
    // TODO: An actual game configuration
    Player p1 = { "Sakari", sf::Color(255, 10, 10) };
    config_ = { true, p1, p1 };
    menu_.Create(&config_, window_.getSize());
    outcome_.Create(window_.getSize());

    AddPlayerPlane(new PlayerPlane(sf::Vector2f(200.f, -600.f), 0.0f, false, 5000, 0.65f, 1));

    // TODO: Fix the enemy plane image so that it doesn't need scaling.
    Plane* plane = new Plane(sf::Vector2f(1000.f, -200.0f), sf::Vector2f(100.f, 100.f), ROOTDIR + "/res/enemy_plane_orange.png", 0.0f, false, 100, 0.0f, 100, 2);
    plane->SetScale(sf::Vector2f(0.15f, 0.15f));
    AddEnemyPlane(plane);
    
    // Add several infantry soldiers
    AddInfantry(10);

    hud_.Create(sf::Vector2f(window_.getSize().x, window_.getSize().y));
    hud_.InitializeValues(player_->GetHP(), enemy_count_, player_->GetAmmoLeft(), "Machine Gun");

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
    for (auto entity : projectiles_)
        delete entity;
    for (auto entity : enemies_)
        delete entity;
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
            case GameState::outcome:
                UpdateOutcome(dt);
                DrawOutcome();
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

void Engine::AddPlane(Plane* plane) {
    planes_.push_back(plane);
}

void Engine::AddEnemyPlane(Plane* plane) {
    AddPlane(plane);
    AddEnemy(plane);
}

void Engine::AddPlayerPlane(PlayerPlane* entity) {
    player_ = entity;
    AddMoving(entity);
    AddPlane(entity);
}

void Engine::AddInfantry(int num) {
    // Add given number of infantry soldiers in x-axis range 0 - 200
    for (int i = 0; i < num; i++) {
        // TODO: Change correct image
        int world_width = world_.GetWidth();
        Infantry *infantry = new Infantry(sf::Vector2f(world_width - randFloat() * world_width / 2, 0.0f), ROOTDIR + "/res/soldier.png" , 0.0f, false, 10 + randFloat() * 20, 250, 0, world_width, 100, 2);
        AddEnemy(infantry);
    }
}

void Engine::AddProjectile(Projectile* entity) {
    projectiles_.push_back(entity);
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
                    case GameState::outcome:
                        ResizeCamera(event.size.width, event.size.height);
                        outcome_.Resize(event.size.width, event.size.height);
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

    // Update the player's state.
    Projectile* p = player_->Act(dt, keys_pressed_);
    if (p != nullptr) {   // If the player has tried to shoot an enemy, add the projectile to moving_entities.
        AddProjectile(p);
    }
    // Update the enemie's states.
    for (auto troop : enemies_) {
        Projectile* p = troop->Act(dt, player_->getPos(), player_->getVelocity());
        if (p != nullptr) {   // If an enemy has tried to shoot the player, add the projectile to moving_entities.
            AddProjectile(p);
        }
    }
    // Update moving entity states
    for (auto entity : moving_entities_) {
        entity->Act(dt);
    }

    // Update projectile states
    for (auto p : projectiles_) {
        p->Act(dt);
    }

    // Update HUD
    hud_.UpdateValues(player_->GetHP(), enemy_count_, player_->GetAmmoLeft());

    CheckProjectileHits();
    CheckGroundHits();
    RemoveDeadEnemies();
    CheckBorders();
    
    if (enemy_count_ == 0) {
        state_ = GameState::outcome;
        outcome_.SetState(true);
    }
    else if (player_->isDead()) {
        state_ = GameState::outcome;
        outcome_.SetState(false);
    }
}

void Engine::DrawGame() {
    window_.clear(backgrounds_.Current().GetBlendColor());
    // Background
    window_.draw(backgrounds_.Current().GetTexture(), backgrounds_.Current().GetTransform());
    // Terrain
    window_.draw(world_.GetGround());
    // Entities
    for(auto& entity : static_entities_)
        window_.draw(entity->getSprite(), entity->getTransform());
    for(auto& entity : moving_entities_)
        window_.draw(entity->getSprite(), entity->getTransform());
    for(auto& troop : enemies_)
        window_.draw(troop->getSprite(), troop->getTransform());
    for(auto& entity : projectiles_)
        window_.draw(entity->getSprite(), entity->getTransform());
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

    // Update menu or options, reset mouse click status
    switch(menu_.GetState()) {
        case MenuState::options:
            menu_.UpdateOptions(mouse_pos_, mouse_clicked_this_frame_);
            break;
        default:
            menu_.Update(mouse_pos_, mouse_clicked_this_frame_);
            break;
    }
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

void Engine::UpdateOutcome(float dt) {
    // Refresh camera view
    CenterCamera();
    window_.setView(camera_);

    // Update background state 
    backgrounds_.Current().Recenter(camera_.getCenter());
    backgrounds_.Current().Update( 50.f * sf::Vector2f(mouse_velocity_.x, mouse_velocity_.y), dt);
}

void Engine::DrawOutcome() {
    window_.clear(backgrounds_.Current().GetBlendColor());
    // Background
    sf::Transform bg_transform = backgrounds_.Current().GetTransform();
    window_.draw(backgrounds_.Current().GetTexture(), bg_transform.translate(0, window_.getSize().y / 2 + 1));
    // Outcome
    window_.draw(outcome_.GetSprite());
    window_.display();
}

void Engine::DrawMenu() {
    window_.clear(backgrounds_.Current().GetBlendColor());
    // Background
    sf::Transform bg_transform = backgrounds_.Current().GetTransform();
    window_.draw(backgrounds_.Current().GetTexture(), bg_transform.translate(0, window_.getSize().y / 2 + 1));
    // Draw menu or options
    switch(menu_.GetState()) {
        case MenuState::options:
            window_.draw(menu_.GetOptionsSprite());
            break;
        default:
            window_.draw(menu_.GetSprite());
            break;
    }

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
    for (auto p : projectiles_) {
        // Check if an enemy was hit by a projectile.
        for (auto enemy : enemies_) {
            if (p->GetTeam() != enemy->GetTeam() && p->WasTroopHit(enemy->getPos())) {
                enemy->ReduceHP(p->GetDamage());
                p->kill();
            }
        }
        // Check if the player was hit by a projectile.
        if (p->GetTeam() != player_->GetTeam() && p->WasTroopHit(player_->getPos())) {
            player_->ReduceHP(p->GetDamage());
            p->kill();
        }
    }

    auto it = projectiles_.begin();
    while (it != projectiles_.end()) {
        // Remove "dead" projectiles, that is projectiles that have already hit a troop -> we can avoid considering the same
        // projectile multiple times.
        if ((*it)->isDead()) {
            delete *it;
            it = projectiles_.erase(it);
        }
        else {
            it++;
        }
    }

}

// Destroy planes that hit the ground;
void Engine::CheckGroundHits() {
    for (auto plane : planes_ ) {
        int plane_y = plane->getPos().y;
        if (plane_y > 0) {
            plane->kill();
        }
    }
}

// Prevent units from flying out of the map
void Engine::CheckBorders() {
    for (auto plane : planes_) {
        const sf::Vector2f& pos = plane->getPos();
        int x = pos.x;
        int y = pos.y;
        if (x < 0) {
            plane->setPos(0, y);
        } else if (pos.x > world_.GetWidth()) {
            plane->setPos(world_.GetWidth(), y);
        }
        if (y < -world_.GetHeight()) {
            plane->setPos(x, -world_.GetHeight());
        }
    }
}

void Engine::RemoveDeadEnemies() {
    auto it = enemies_.begin();
    while (it != enemies_.end()) {
        if ((*it)->isDead()) {
            delete *it;
            it = enemies_.erase(it);
            enemy_count_--;
        }
        else {
            it++;
        }
    }
}