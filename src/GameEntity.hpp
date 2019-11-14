#pragma once

#include <SFML/Graphics.hpp>

/* GameEntity represents a game object with a position, rotation, sprite and status.
   All game objects inherit this class. */
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
    const bool isDead() const;
    void setRepeated(bool set);
    void setTextureRect(sf::IntRect r);
    void kill();
protected:
    sf::Vector2f pos_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    float rotation_;
    bool dead_;
};
