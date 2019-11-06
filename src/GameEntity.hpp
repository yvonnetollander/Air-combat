#include <SFML/Graphics.hpp>

class GameEntity {
public:
    GameEntity();
    GameEntity(const sf::Vector3f& p, const sf::Texture& t, const float r, const bool d);
    const sf::Vector3f getPos() const;
    void SetPos(const sf::Vector3f& p);
    const bool isDead() const;
    void kill();
private:
    sf::Vector3f pos_;
    sf::Texture sprite_;
    float rotation_;
    bool dead_;
};
