#pragma once

#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"
#include "MovingEntity.hpp"
#include "CombatEntity.hpp"
#include "Plane.hpp"
#include <map>
#include "util.hpp"
#include "Background.hpp"

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
    void AddStatic(GameEntity* entity);
    void AddCombat(CombatEntity* entity);
    void AddPlayer(PlayerPlane* entity);
    void AddCombatNextFrame(CombatEntity* entity);

private:
    float target_aspect_ratio_ = 16.f / 9.f;
    sf::RenderWindow window_;
    sf::RectangleShape ground_;
    sf::View camera_;
    sf::RenderTexture foreground_;
    sf::RenderTexture background_;
    std::vector<GameEntity*> static_entities_;
    std::vector<MovingEntity*> moving_entities_;
    std::vector<CombatEntity*> combat_entities_;
    std::vector<CombatEntity*> new_combat_entities_;
    PlayerPlane* player_;

    Keys keys_pressed_;
    Background bg_;

    void Update(float dt);
    void Draw();
    void Input(sf::Event& event);
    // Resets camera to given resolution
    void resetView(const float w, const float h);
};
