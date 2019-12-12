#pragma once

#include <SFML/Graphics.hpp>

/*  GameEntity represents a game object.
    Parameters for the constructor:
    p: position
    spritepath: illustration of the object
    r: objects rotation in degrees as a float
    d: boolean of the objects status. True: object is alive, false: objects is dead or destroyed.
    All game objects inherit this class. 
*/
class GameEntity {
public:
    GameEntity();
    GameEntity(const sf::Vector2f& p, const std::string spritepath, const float r, const bool d);
    const sf::Vector2f getPos() const;
    const sf::Vector2u getSize() const;
    const sf::Sprite& getSprite() const;
    // Compute and return object-to-world transform
    const sf::Transform getTransform() const;
    void setPos(const sf::Vector2f& p);
    void setPos(int x, int y);
    // Increase objects rotation the amount of degrees given as parameter deg
    void Rotate(const float deg);
    // Set objects rotation to given parameter deg
    void SetRotation(const float deg);
    void SetScale(const sf::Vector2f scale);
    // Return objects status if the object is dead or alive
    const bool isDead() const;
    void setRepeated(bool set);
    void setOrigin(sf::Vector2f origin);
    void setTextureRect(sf::IntRect r);
    // Set protected variable dead_ true
    void kill();
protected:
    // GameEntity position
    sf::Vector2f pos_;
    // GameEntity texture 
    sf::Texture texture_;
    // GameEntity sprite 
    sf::Sprite sprite_;
    // GameEntitys rotation in degrees
    float rotation_;
    // GameEntity status if the entity is dead or alive
    bool dead_;
};
