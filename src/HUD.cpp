#include "HUD.hpp"

#include <string>

#include "globals.hpp"
#include "util.hpp"

/* ****** HUD ****** */
HUD::HUD() {
    transform_ = sf::Transform().translate(0, 2000);
    // Set positions for four informative texts
    text_[0] = CreatePositionedText("", 20, 5, 18, sf::Color::White);
    text_[1] = CreatePositionedText("", 300, 5, 18, sf::Color::White);
    text_[2] = CreatePositionedText("", 20, 30, 18, sf::Color::White);
    text_[3] = CreatePositionedText("", 300, 30, 18, sf::Color::White);
    // Set background color as dark purple
    background_.setFillColor(sf::Color(25, 0, 50));
    background_.setOrigin(0,0);
}

void HUD::Create(const sf::Vector2f size) {
    size_.x = size.x;
    size_.y = size.y / 10;
    background_.setSize(sf::Vector2f(size_.x, size_.y));
    render_texture_.create(size_.x, size_.y);
}

void HUD::InitializeValues(const unsigned hp, const unsigned enemies, const unsigned ammo, std::string weapon) {
    max_hp_ = hp;
    hp_ = hp;
    total_enemies_ = enemies;
    enemies_ = enemies;
    total_ammo_ = ammo;
    ammo_ = ammo;
    weapon_ = weapon;
} 

const sf::Transform HUD::GetTransform() const {
    return transform_;
}

void HUD::Resize(const float base_width, const float base_height) {
    size_.x = base_width;
    size_.y = base_height / 10;
    background_.setSize(sf::Vector2f(size_.x, size_.y));
    render_texture_.create(size_.x, size_.y);
}

const sf::Sprite HUD::GetSprite() {
    UpdateTexts(); 
    render_texture_.clear(sf::Color(255, 255, 255));
    render_texture_.draw(background_);
    render_texture_.draw(text_[0]);
    render_texture_.draw(text_[1]);
    render_texture_.draw(text_[2]);
    render_texture_.draw(text_[3]);
    render_texture_.display();
    t_ = render_texture_.getTexture();
    s_ = sf::Sprite (t_);
    return s_;
}

void HUD::UpdateValues(const unsigned hp, const unsigned enemies, const unsigned ammo) {
    hp_ = hp;
    enemies_ = enemies;
    ammo_ = ammo;
} 

void HUD::UpdateTexts() {
    text_[0].setString("Health points: "  + std::to_string(hp_) + "/" + std::to_string(max_hp_));
    text_[1].setString("Weapon: " + weapon_);
    text_[2].setString("Enemies: "  + std::to_string(enemies_) + "/" + std::to_string(total_enemies_));
    text_[3].setString("Ammo: "  + std::to_string(ammo_) + "/" + std::to_string(total_ammo_));
}