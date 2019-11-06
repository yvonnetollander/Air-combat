#pragma once
#include <SFML/Graphics.hpp>

/* A simple class for the game engine.
*  Start the engine calling the Start() method.
*/
class Engine {
private:
    sf::RenderWindow window_;
    sf::Sprite background_sprite_;
    sf::Texture background_texture_;

    // void update(float dt);
    void Draw();

public:
    Engine();
    void Start();
};