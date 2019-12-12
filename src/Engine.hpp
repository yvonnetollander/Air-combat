#pragma once

#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"
#include "MovingEntity.hpp"
#include "Plane.hpp"
#include <map>
#include "util.hpp"
#include "Background.hpp"
#include "Config.hpp"
#include "Menu.hpp"
#include "HUD.hpp"
#include "Infantry.hpp"
#include "Outcome.hpp"
#include "World.hpp"
#include "Explosion.hpp"
#include "Minimap.hpp"

/* A simple class for the game engine.
*  Contains all the game entities and handles the refresh, draw and input loops.
*  Start the engine calling the Start() method.
*/
class Engine {
public:
    Engine();
    ~Engine();
    void Start();
    void AddMoving(MovingEntity* entity);
    void AddEnemy(Troop* entity);
    void AddStatic(GameEntity* entity);
    void AddPlane(Plane* plane);
    void AddEnemyPlane(Plane* plane);
    void AddPlayerPlane(PlayerPlane* entity);
    void AddProjectile(Projectile* entity);
    void AddExplosion(Explosion* explosion);
    void ClearEntities();
    void InitializeGame();
private:
    GameState state_;
    Config config_;
    const float target_aspect_ratio_ = 16.f / 9.f;
    sf::RenderWindow window_;
    World world_;
    sf::View camera_;
    HUD hud_;
    sf::RenderTexture background_;
    std::vector<GameEntity*> static_entities_;
    std::vector<MovingEntity*> moving_entities_;
    std::vector<Troop*> enemies_;
    std::vector<Projectile*> projectiles_;
    std::vector<Plane*> planes_;
    std::vector<Explosion*> explosions_;
    PlayerPlane* player_;

    Keys keys_pressed_;
    BackgroundSet backgrounds_;
    Menu menu_;
    Minimap minimap_;
    Outcome outcome_;

    unsigned enemy_count_ = 0;

    // Mouse movement tracking for menu parallax effect and buttons
    sf::Vector2i mouse_pos_;
    sf::Vector2i mouse_velocity_;
    bool mouse_clicked_this_frame_;

    // Create number of infantry soldiers
    void AddInfantry(int num);
    // Generate enemy planes.
    void GeneratePlanes(int num);

    void CheckProjectileHits();
    void RemoveDeadEnemies();
    void RemoveDeadPlanes();
    void RemoveDeadExplosions();
    
    void CheckGroundHits();
    void CheckBorders();

    // In-game logic and drawing
    void UpdateGame(float dt);
    void DrawGame();

    // In-menu logic and drawing
    void UpdateMenu(float dt);
    void DrawMenu();
    
    // Game outcome drawing
    void UpdateOutcome(float dt);
    void DrawOutcome();

    // User input handling
    void Input(sf::Event& event);
    // Resets camera to given resolution
    void ResizeCamera(const float w, const float h);
    // Centers camera to starting position (middle of window size)
    // Used centering the menu
    void CenterCamera();
};
