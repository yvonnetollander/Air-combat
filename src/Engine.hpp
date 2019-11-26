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
    void AddPlayerPlane(PlayerPlane* entity);

private:
    GameState state_;
    Config config_;
    const float target_aspect_ratio_ = 16.f / 9.f;
    sf::RenderWindow window_;
    sf::RectangleShape ground_;
    sf::View camera_;
    HUD hud_;
    sf::RenderTexture background_;
    std::vector<GameEntity*> static_entities_;
    std::vector<MovingEntity*> moving_entities_;
    std::vector<Troop*> enemies_;
    PlayerPlane* player_;

    Keys keys_pressed_;
    BackgroundSet backgrounds_;
    Menu menu_;

    // Mouse movement tracking for menu parallax effect and buttons
    sf::Vector2i mouse_pos_;
    sf::Vector2i mouse_velocity_;
    bool mouse_clicked_this_frame_;


    // In-game logic and drawing
    void UpdateGame(float dt);
    void DrawGame();

    // In-menu logic and drawing
    void UpdateMenu(float dt);
    void DrawMenu();
    
    void Input(sf::Event& event);
    // Resets camera to given resolution
    void ResizeCamera(const float w, const float h);
    // Centers camera to starting position (middle of window size)
    // Used centering the menu
    void CenterCamera();
};
