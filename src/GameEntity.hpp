#include <SFML/Graphics.hpp>

class GameEntity {
public:
    GameEntity() {}
    const sf::Vector3f getPos() const;
    void SetPos(const sf::Vector3f& p);
    const bool isDead() const;
private:
    sf::Vector3f pos_;
    sf::Texture sprite_;
    float rotation_;
    bool dead_;
};
