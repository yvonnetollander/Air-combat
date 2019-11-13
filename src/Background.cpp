#include <cmath>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include "globals.hpp"

Background::Background() {
    sky_tex_.loadFromFile(ROOTDIR + "/res/parallax-mountain-bg.png");
    sky_tex_.setRepeated(true);
    sky_sprite_.setTexture(sky_tex_);

    bg_mountain_tex_.loadFromFile(ROOTDIR + "/res/parallax-mountain-montain-far.png");
    bg_mountain_tex_.setRepeated(true);
    bg_mountain_sprite_.setTexture(bg_mountain_tex_);
    //bg_mountain_sprite_.setTextureRect({ 0, 0, bg_mountain_tex_.getSize().x * 2, bg_mountain_tex_.getSize().y });

    fg_mountain_tex_.loadFromFile(ROOTDIR + "/res/parallax-mountain-mountains.png");
    fg_mountain_tex_.setRepeated(true);
    fg_mountain_sprite_.setTexture(fg_mountain_tex_);
    //fg_mountain_sprite_.setTextureRect({ 0, 0, fg_mountain_tex_.getSize().x * 2, fg_mountain_tex_.getSize().y });

    bg_tree_tex_.loadFromFile(ROOTDIR + "/res/parallax-mountain-trees.png");
    bg_tree_tex_.setRepeated(true);
    bg_tree_sprite_.setTexture(bg_tree_tex_);
    //bg_tree_sprite_.setTextureRect({ 0, 0, bg_tree_tex_.getSize().x * 2, bg_tree_tex_.getSize().y });

    fg_tree_tex_.loadFromFile(ROOTDIR + "/res/parallax-mountain-foreground-trees.png");
    fg_tree_tex_.setRepeated(true);
    fg_tree_sprite_.setTexture(fg_tree_tex_);
    //fg_tree_sprite_.setTextureRect({ 0, 0, fg_tree_tex_.getSize().x * 2, fg_tree_tex_.getSize().y });
}

void Background::update(const sf::Vector2f& v, const float& dt) {
    float d = std::round(v.x * dt);
    bg_mountain_scroll_ = std::fmod(d * 0.2f + bg_mountain_scroll_, 272);
    fg_mountain_scroll_ = std::fmod(d * 0.33f + fg_mountain_scroll_, 544);
    bg_tree_scroll_ = std::fmod(d * 0.47f + bg_tree_scroll_, 544);
    fg_tree_scroll_ = std::fmod(d * 0.6f + fg_tree_scroll_, 544);
    
    sky_transform_ = sf::Transform().translate(sf::Vector2f(-sky_scroll_, 0));
    bg_mountain_transform_ = sf::Transform().translate(sf::Vector2f(-bg_mountain_scroll_, 0));
    fg_mountain_transform_ = sf::Transform().translate(sf::Vector2f(-fg_mountain_scroll_, 0));
    bg_tree_transform_ = sf::Transform().translate(sf::Vector2f(-bg_tree_scroll_, 0));
    fg_tree_transform_ = sf::Transform().translate(sf::Vector2f(-fg_tree_scroll_, 0));
}

const sf::Texture& Background::GetTexture() {
    std::cout << bg_mountain_scroll_ << std::endl;
    tx_.clear();
    tx_.create(1088, 320);
    tx_.draw(sky_sprite_, sf::RenderStates(sky_transform_));
    tx_.draw(bg_mountain_sprite_, sf::RenderStates(bg_mountain_transform_));
    tx_.draw(fg_mountain_sprite_, sf::RenderStates(fg_mountain_transform_));
    tx_.draw(bg_tree_sprite_, sf::RenderStates(bg_tree_transform_));
    tx_.draw(fg_tree_sprite_, sf::RenderStates(fg_tree_transform_));

    tx_.display();
    return tx_.getTexture();
}
