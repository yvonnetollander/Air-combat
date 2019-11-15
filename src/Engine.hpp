#pragma once

#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"
#include "MovingEntity.hpp"
#include "Plane.hpp"
#include <map>
#include "util.hpp"

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
    void AddPlayer(PlayerPlane* entity);

private:
    float target_aspect_ratio_ = 16.f / 9.f;
    sf::RenderWindow window_;
    sf::Sprite background_sprite_;
    sf::Texture background_texture_;
    sf::View camera_;
    std::vector<GameEntity*> static_entities_;
    std::vector<MovingEntity*> moving_entities_;
    PlayerPlane* player_;

    Keys keys_pressed_;

    void Update(float dt);
    void Draw();
    void Input(sf::Event& event);
    // Letterboxes/corrects the camera viewport to match target_aspect_ratio_
    void ResetView();
};
