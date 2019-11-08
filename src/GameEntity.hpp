#include <SFML/Graphics.hpp>

/* GameEntity represents a game object with a position, rotation, sprite and status.
   All game objects inherit this class. */
class GameEntity {
public:
    GameEntity();
    GameEntity(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d);
    const sf::Vector2f getPos() const;
    void SetPos(const sf::Vector2f& p);
    const bool isDead() const;
    void kill();
private:
    sf::Vector2f pos_;
    sf::Texture sprite_;
    float rotation_;
    bool dead_;
};
