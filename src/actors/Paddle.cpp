#include "../../include/Actors/Paddle.hpp"

Paddle::Paddle() {}

Paddle::~Paddle() {}

void Paddle::Initialize() {
    shape_.setSize(sf::Vector2f({PADDLE_WIDTH, PADDLE_HEIGHT}));
    shape_.setFillColor(sf::Color::White);

    Actor::Initialize();
}

void Paddle::Draw(sf::RenderWindow& window) {
    window.draw(shape_);
}

void Paddle::SetPosition(float x, float y) {
    position_ = sf::Vector2f(x, y);
    shape_.setPosition({x, y});
}

sf::Vector2f Paddle::GetPosition() const {
    return position_;
}