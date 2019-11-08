#include <Troop.hpp>

class Plane : public Troop {
public:
    Plane();
    Plane(const sf::Vector2f& p, const sf::Texture& t, const float r, const bool d, const unsigned hp, float drag);
    virtual void act(float dt) {}
    void act(float dt, bool left, bool right, bool down, bool up);
private:
    bool thrust_;
    bool inverted_;
    float drag_;
    sf::Vector2f velocity_;
};
