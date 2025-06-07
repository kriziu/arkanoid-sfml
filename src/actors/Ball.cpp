#include "../../include/Actors/Ball.hpp"

Ball::Ball() : Actor(), velocity_(0, 0), attachedToPaddle_(true), initialLaunchBlocked_(true), lives_(3) {}

Ball::~Ball() {}

void Ball::Initialize() {
    shape_.setRadius(BALL_RADIUS);
    shape_.setFillColor(sf::Color::White);
    shape_.setOrigin(sf::Vector2f(BALL_RADIUS, BALL_RADIUS));
    
    Actor::Initialize();
}

void Ball::Draw(sf::RenderWindow& window) {
    window.draw(shape_);
}

void Ball::SetPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
    shape_.setPosition(position_);
}

sf::Vector2f Ball::GetPosition() const {
    return position_;
}

void Ball::SetVelocity(float x, float y) {
    velocity_.x = x;
    velocity_.y = y;
}

sf::Vector2f Ball::GetVelocity() const {
    return velocity_;
}

bool Ball::IsAttachedToPaddle() const {
    return attachedToPaddle_;
}

bool Ball::IsInitialLaunchBlocked() const {
    return initialLaunchBlocked_;
}

void Ball::SetAttachedToPaddle(bool attached) {
    attachedToPaddle_ = attached;
}

void Ball::SetInitialLaunchBlocked(bool blocked) {
    initialLaunchBlocked_ = blocked;
}

sf::FloatRect Ball::GetBounds() const {
    return shape_.getGlobalBounds();
}

int Ball::GetLives() const {
    return lives_;
}

void Ball::SetLives(int lives) {
    lives_ = lives;
}

void Ball::DecrementLives() {
    lives_--;
} 