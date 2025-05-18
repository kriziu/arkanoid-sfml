#include "../../include/Actors/Paddle.hpp"
#include "../../include/Utils/Constants.hpp"

Paddle::Paddle(){}

Paddle::~Paddle() {}

void Paddle::Initialize() {
    shape_.setSize(sf::Vector2f({paddleWidth, paddleHeight}));
    shape_.setFillColor(sf::Color::White);
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