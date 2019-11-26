#include "HUD.hpp"
#include "globals.hpp"
#include <iostream>
#include <string>

/* ****** HUD ****** */
HUD::HUD() {
    transform_ = sf::Transform().translate(0, 2000);

    text_[0].setFont(AirCombatFonts::roboto_regular);
    text_[0].setFillColor(sf::Color::White);
    text_[0].setPosition(20,5);
    text_[0].setCharacterSize(18);

    text_[1].setFont(AirCombatFonts::roboto_regular);
    text_[1].setFillColor(sf::Color::White);
    text_[1].setPosition(300,5);
    text_[1].setCharacterSize(18);

    text_[2].setFont(AirCombatFonts::roboto_regular);
    text_[2].setFillColor(sf::Color::White);
    text_[2].setPosition(20, 30);
    text_[2].setCharacterSize(18);

    text_[3].setFont(AirCombatFonts::roboto_regular);
    text_[3].setFillColor(sf::Color::White);
    text_[3].setPosition(300, 30);
    text_[3].setCharacterSize(18);

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
    text_[0].setString("Hitpoints: "  + std::to_string(hp_) + "/" + std::to_string(max_hp_));
    text_[1].setString("Weapon: " + weapon_);
    text_[2].setString("Enemies: "  + std::to_string(enemies_) + "/" + std::to_string(total_enemies_));
    text_[3].setString("Ammo: "  + std::to_string(ammo_) + "/" + std::to_string(total_ammo_));
}