#include <cmath>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include "globals.hpp"

ScrollingBackdrop::ScrollingBackdrop(const std::string spritepath, const float velocity, const float static_velocity = 0.f)
    : MovingEntity(sf::Vector2f(), sf::Vector2f(), spritepath, 0.f, false), velocity_(velocity), static_velocity_(static_velocity), view_velocity_()
{
    setOrigin(sf::Vector2f(0, 0));
    // Repeat sprite two times to the right, we will later move one full width
    // to the left to have one repeat on each side
    setRepeated(true);
    setTextureRect(sf::IntRect(0, 0, getSize().x * 3, getSize().y));
}

Projectile* ScrollingBackdrop::Act(float dt) {
    // Movement relative to v
    const float dx = velocity_ * view_velocity_.x * movement_scale_.x * dt;
    // Static movement
    const float static_dx = static_velocity_ * movement_scale_.x * dt;
    // Move & clip back to original position when we go over a full width
    sf::Vector2f pos = getPos();
    setPos(sf::Vector2f(std::fmod(pos.x - dx - static_dx, getSize().x * movement_scale_.x), pos.y));
    return nullptr;
}

void ScrollingBackdrop::SetViewVelocity(sf::Vector2f v) {
    view_velocity_ = v;
}

void ScrollingBackdrop::SetMovementScale(sf::Vector2f s) {
    movement_scale_ = s;
}

Background::Background(const sf::Vector2u size)
    : size_(size), scale_({1.f, 1.f}), repeats_(1u), blend_color_(sf::Color::Black) {}

Background::~Background() {
    for(auto entity : backdrops_)
        delete entity;
}

void Background::SetScale(sf::Vector2f scale) {
    scale_ = scale;
    render_texture_.create(size_.x * scale_.x, size_.y * scale_.y);
    for(auto entity : backdrops_)
        entity->SetMovementScale(scale_);
}

void Background::SetRepetition(unsigned repeats) {
    repeats_ = repeats;
}

void Background::CorrectRepetition() {
    // Compute the repetitions we need to fit the screen, again taking
    // into account scaling
    unsigned repetitions = ((float) base_size_.x / (float) size_.x / scale_.x) + 1;
    // Round up to an odd number to align things nicely
    repetitions += (repetitions + 1) % 2;
    SetRepetition(repetitions);
}

void Background::SetBlendColor(const sf::Color color) {
    blend_color_ = color;
}

const sf::Color Background::GetBlendColor() const {
    return blend_color_;
}

void Background::AddBackdrop(ScrollingBackdrop* backdrop) {
    backdrop->SetMovementScale(scale_);
    backdrops_.push_back(backdrop);
}

void Background::Update(sf::Vector2f v, const float dt) {
    for(auto& entity : backdrops_) {
        entity->SetViewVelocity(v);
        entity->Act(dt);
    }
}

const sf::Sprite Background::GetTexture() {
    render_texture_.clear(sf::Color::Transparent);

    // Draw backdrops
    for(auto& entity : backdrops_) {
        auto transform = entity->getTransform();
        auto sprite = entity->getSprite();
        sprite.setScale(scale_);
        // Additionally translate one full width to the left
        render_texture_.draw(sprite, sf::RenderStates(transform.translate(-scale_.x * size_.x, 0)));
    }
    render_texture_.display();
    texture_ = render_texture_.getTexture();

    // Apply repetition
    texture_.setRepeated(true);
    sprite_ = sf::Sprite(texture_);
    sprite_.setOrigin(size_.x*scale_.x/2, size_.y*scale_.y);
    sprite_.setTextureRect(sf::IntRect(0, 0, texture_.getSize().x * repeats_, texture_.getSize().y));

    return sprite_;
}

 const sf::Transform Background::GetTransform() const {
     sf::Transform t(transform_);
     return t.translate(pos_);
 }

void Background::FitToScreen(const sf::Vector2u base_size, const float scale, const float height = 0.f) {
    base_size_ = base_size;
    height_offset_ = -height;
    SetScale(sf::Vector2f(scale, scale));
    Resize(base_size.x, base_size.y);
}

void Background::Recenter(const sf::Vector2f camera_center) {
    // Reset position and realign
    pos_ = sf::Vector2f();
    Move(camera_center.x, height_offset_);
}

void Background::Move(const float w, const float h) {
    pos_ += sf::Vector2f(w, h);
}

void Background::Resize(const float base_width, const float base_height) {
    base_size_ = sf::Vector2u(base_width, base_height);
    // Recompute needed repetition
    CorrectRepetition();
    // Update transform to center the background on bottom border
    transform_ = sf::Transform().translate(-1.f * (repeats_ / 2) * size_.x * scale_.x,  0);
}

const sf::Vector2f Background::GetPos() {
    return pos_;
}

const sf::Vector2f Background::GetScale() {
    return scale_;
}

const sf::Vector2u Background::GetBaseSize() {
    return base_size_;
}

 const float Background::GetHeightOffset() {
     return height_offset_;
 }

Background* MountainBackground() {
    Background* bg = new Background(sf::Vector2u(272,160));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/mountains_0.png", 0, -5));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/mountains_1.png", 0.20f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/mountains_2.png", 0.33f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/mountains_3.png", 0.50f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/mountains_4.png", 0.75f));
    bg->SetBlendColor(sf::Color(171, 106, 140));
    return bg;
}

Background* IndustrialBackground() {
    Background* bg = new Background(sf::Vector2u(272,160));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/industrial_0.png", 0.10f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/industrial_1.png", 0.20f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/industrial_2.png", 0.33f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/industrial_3.png", 0.50f));
    bg->SetBlendColor(sf::Color(25, 40, 31));
    return bg;
}

Background* UnderwaterBackground() {
    Background* bg = new Background(sf::Vector2u(512,192));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/underwater_0.png", 0.10f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/underwater_1.png", 0.20f));
    bg->AddBackdrop(new ScrollingBackdrop(ROOTDIR + "/res/underwater_2.png", 0.33f));
    bg->SetBlendColor(sf::Color(62, 121, 221));
    return bg;
}

BackgroundSet::BackgroundSet() : current_idx_(0u) {
    backgrounds_.push_back(MountainBackground());
    backgrounds_.push_back(IndustrialBackground());
    backgrounds_.push_back(UnderwaterBackground());
}

BackgroundSet::~BackgroundSet() {
    for (auto bg : backgrounds_) 
        delete bg;
}

Background& BackgroundSet::Current() {
    return *backgrounds_[current_idx_];
}

void BackgroundSet::Switch() {
    const unsigned new_idx = (current_idx_ + 1) % backgrounds_.size();

    // Fit new background identically to previous
    const sf::Vector2u base_size = backgrounds_[current_idx_]->GetBaseSize();
    const float scale =  backgrounds_[current_idx_]->GetScale().x;
    const float height_offset = backgrounds_[current_idx_]->GetHeightOffset();
    backgrounds_[new_idx]->FitToScreen(base_size, scale, -height_offset);

    current_idx_ = new_idx;
}