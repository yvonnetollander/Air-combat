#pragma once

#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"
#include "MovingEntity.hpp"

struct Keys {
    bool up = false;    // flip
    bool down = false;  // stop engine
    bool left = false;  // rotate
    bool right = false; // rotate
    bool d = false;     // shoot
};

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

private:
    sf::RenderWindow window_;
    sf::Sprite background_sprite_;
    sf::Texture background_texture_;
    std::vector<GameEntity*> static_entities_;
    std::vector<MovingEntity*> moving_entities_;
    Keys keys_pressed_;

    void Update(float dt);
    void Draw();
    void Input(sf::Event& event);
};
