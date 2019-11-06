#include <iostream>
#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Engine.cpp"

int main()
{
    /*
    std::cout << "Hello world!\nBehold this spinning cross." << std::endl;

    sf::RectangleShape r1(sf::Vector2f(150, 50));
    sf::RectangleShape r2(sf::Vector2f(50, 150));

    r1.setOrigin(sf::Vector2f(75,25));
    r2.setOrigin(sf::Vector2f(25,75));

    r1.setPosition(sf::Vector2f(150, 150));
    r2.setPosition(sf::Vector2f(150, 150));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape) )
            {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        r1.rotate(0.01f);
        r2.rotate(0.01f);

        window.draw(r1);
        window.draw(r2);

        window.display();
    }*/

    Engine engine;
    engine.Start();
    

    return 0;
}