#include "HUD.hpp"
#include "globals.hpp"
#include <iostream>
#include <string>

/* ****** HUD ****** */
HUD::HUD() {
    transform_ = sf::Transform().translate(0, 2000);

    if(!font.loadFromFile(ROOTDIR + "/res/Roboto-Regular.ttf")) {
        //error
    }
    text_[0].setFont(font);
    text_[0].setFillColor(sf::Color::Black);
    text_[0].setPosition(0,0);
    text_[0].setCharacterSize(15);

    text_[1].setFont(font);
    text_[1].setFillColor(sf::Color::Black);
    text_[1].setPosition(400,0);

    text_[2].setFont(font);
    text_[2].setFillColor(sf::Color::Black);
    text_[2].setPosition(0, 40);

    text_[3].setFont(font);
    text_[3].setFillColor(sf::Color::Black);
    text_[3].setPosition(400, 40);

    background_.setSize(sf::Vector2f(500, 500));
    background_.setFillColor(sf::Color(255, 255, 0));
    background_.setOrigin(0,0);

    max_hp_ = 100;
    total_enemies_ = 20;
    total_ammo_ = 30;
}

void HUD::Create(const sf::Vector2f size) {
    render_texture_.create(size.x, size.y);
}

const sf::Transform HUD::GetTransform() const {
    return transform_;
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
    text_[1].setString("Weapon: " );
    text_[2].setString("Enemies: "  + std::to_string(enemies_) + "/" + std::to_string(total_enemies_));
    text_[3].setString("Ammo: "  + std::to_string(ammo_) + "/" + std::to_string(total_ammo_));
}