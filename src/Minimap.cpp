#include "Minimap.hpp"

#include <iostream>

Minimap::Minimap() : size_(1000,0) {
    anchor_ = sf::Vector2f(30, 30);
}

void Minimap::Align(unsigned x, unsigned y) {
    anchor_ = sf::Vector2f(x, y);
}

void Minimap::SetWorldSize(int x, int y) {
    worldsize_ = sf::Vector2f(x, y);
    size_.y = (float(y) / float(x)) * size_.x;
    render_texture_.create(size_.x, size_.y);
}

sf::Vector2f Minimap::TransformWorldToMap(sf::Vector2f vec) {
    return sf::Vector2f((size_.x/worldsize_.x) * vec.x, (size_.y/worldsize_.y) * vec.y + size_.y);
}

void Minimap::SetCamera(sf::View camera) {
    camera_ = camera;
}

void Minimap::DrawOnMap(sf::Vector2f pos, const float size, const sf::Color color) {
    pos = TransformWorldToMap(pos);

    sf::CircleShape dot(size);
    dot.setFillColor(color);
    dot.setPosition(pos);
    dot.setOrigin(dot.getRadius(), dot.getRadius());
    render_texture_.draw(dot);
}

const sf::Sprite Minimap::GetSprite(std::vector<MovingEntity*>& players, std::vector<Troop*>& enemies, std::vector<Projectile*>& projectiles, std::vector<Explosion*>& explosions) {
    render_texture_.clear(sf::Color(0, 0, 0, 100));

    std::vector<sf::Vector2f> dots;
    for (auto& entity : players)
        DrawOnMap(entity->getPos(), 7.f, sf::Color::Blue);
    for (auto& entity : enemies)
        DrawOnMap(entity->getPos(), 4.f, sf::Color::Red);
    for (auto& entity : projectiles)
        DrawOnMap(entity->getPos(), 1.f, sf::Color::Yellow);
    for (auto& entity : explosions)
        DrawOnMap(entity->getPos() +sf::Vector2f(-96*5.5f*entity->GetScale(),0), 12.f, sf::Color(245, 230, 66, 200));

    sf::RectangleShape r;
    r.setSize(sf::Vector2f((camera_.getSize().x/worldsize_.x) * size_.x, (camera_.getSize().y/worldsize_.y) * size_.y));
    r.setOrigin(r.getSize().x/2, r.getSize().y/2);
    r.setFillColor(sf::Color(255,255,255,60));
    r.setOutlineThickness(1);
    r.setOutlineColor(sf::Color(200, 0, 0));
    r.setPosition(TransformWorldToMap(camera_.getCenter()));
    render_texture_.draw(r);

    render_texture_.display();
    t_ = render_texture_.getTexture();
    r.setFillColor(sf::Color::Blue);
    s_ = sf::Sprite(t_);
    s_.setPosition(anchor_ + padding_);
    s_.setOrigin(t_.getSize().x, t_.getSize().y);
    return s_; 
}
